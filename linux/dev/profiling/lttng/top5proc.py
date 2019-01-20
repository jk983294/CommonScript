from collections import Counter
import babeltrace
import sys


def top5proc():
    if len(sys.argv) != 2:
        msg = 'Usage: python3 {} TRACEPATH'.format(sys.argv[0])
        print(msg, file=sys.stderr)
        return False

    # A trace collection contains one or more traces
    col = babeltrace.TraceCollection()

    # Add the trace provided by the user (LTTng traces always have
    # the 'ctf' format)
    if col.add_trace(sys.argv[1], 'ctf') is None:
        raise RuntimeError('Cannot add trace')

    # This counter dict contains execution times:
    #
    #   task command name -> total execution time (ns)
    exec_times = Counter()

    # This contains the last `sched_switch` timestamp
    last_ts = None

    # Iterate on events
    for event in col.events:
        # Keep only `sched_switch` events
        if event.name != 'sched_switch':
            continue

        # Keep only events which happened on CPU 0
        if event['cpu_id'] != 0:
            continue

        # Event timestamp
        cur_ts = event.timestamp

        if last_ts is None:
            # We start here
            last_ts = cur_ts

        # Previous task command (short) name
        prev_comm = event['prev_comm']

        # Initialize entry in our dict if not yet done
        if prev_comm not in exec_times:
            exec_times[prev_comm] = 0

        # Compute previous command execution time
        diff = cur_ts - last_ts

        # Update execution time of this command
        exec_times[prev_comm] += diff

        # Update last timestamp
        last_ts = cur_ts

    # Display top 5
    for name, ns in exec_times.most_common(5):
        s = ns / 1000000000
        print('{:20}{} s'.format(name, s))

    return True


if __name__ == '__main__':
    sys.exit(0 if top5proc() else 1)
