#!/opt/anaconda3/bin/python3
import fileinput
import re


def get_time(str_time):
    lets1 = str_time.split('.')
    lets2 = lets1[0].split(':')
    t = float(lets2[0]) * 60 * 60 + float(lets2[1]) * 60 + float(lets2[2]) + float(lets1[1]) * 1e-9
    return t


class StatItem:
    def __init__(self, prefix, step_num, ts):
        self.prefix = prefix
        self.steps = [step_num]
        self.steps_ts = [ts]

    def add(self, step_num, ts):
        if len(self.steps) == 0 or self.steps[-1] < step_num:
            self.steps.append(step_num)
            self.steps_ts.append(ts)
        else:
            self.print_item()
            self.steps.append(step_num)
            self.steps_ts.append(ts)

    def print_item(self):
        size = len(self.steps_ts)
        if size > 1:
            bench_ts = self.steps_ts[0]
            for i in range(size - 1):
                print(self.steps_ts[i + 1] - bench_ts, end=' ')
            print('%s_%d' % (self.prefix, self.steps[-1]))
        self.steps.clear()
        self.steps_ts.clear()


class Stats:
    def __init__(self):
        self.prefix2item = {}

    def add_item(self, ts, desc):
        lets = desc.split('_')
        if len(lets) == 2:
            step_num = int(lets[1])
            desc_prefix = lets[0]
            if desc_prefix in self.prefix2item:
                self.prefix2item[desc_prefix].add(step_num, ts)
            else:
                self.prefix2item[desc_prefix] = StatItem(desc_prefix, step_num, ts)
        else:
            print('description format not correct, should be prefix_num')

    def print_left(self):
        for p, item in self.prefix2item.items():
            item.print_item()


line_reg_exp = re.compile(r'\[(.+)\].+{.+}.+{.+id\s+=\s+(-?\d+),.+"(.+)" }')
stats = Stats()

# typic input
# [12:24:45.373617430] (+0.000010567) dev2 Phoenix:phx_tracepoint: { cpu_id = 4 }, { file = "OrderServer.cpp", func = "OnSocketRead", line = 159, id = -1, desc = "step_2" }
with fileinput.input() as f_input:
    for line in f_input:
        if line_reg_exp.match(line):
            groups = line_reg_exp.match(line).groups()
            timestamp = get_time(groups[0])
            id_ = groups[1]
            desc = groups[2]
            stats.add_item(timestamp, desc)

stats.print_left()
