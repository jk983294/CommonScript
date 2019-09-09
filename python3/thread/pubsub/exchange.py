from collections import defaultdict


class Exchange:
    def __init__(self):
        self._subscribers = set()

    def register_subscriber(self, task):
        self._subscribers.add(task)

    def unsubscribe(self, task):
        self._subscribers.remove(task)

    def publish(self, msg):
        for subscriber in self._subscribers:
            subscriber.publish(msg)


# Dictionary of all created exchanges
_exchanges = defaultdict(Exchange)


# Return the Exchange instance associated with a given name
def get_exchange(name):
    return _exchanges[name]


# Example of a task.  Any object with a publish() method

class Task:
    def publish(self, msg):
        print("process msg:", msg)


task_a = Task()
task_b = Task()

# Example of getting an exchange
exc = get_exchange('name')

# Examples of subscribing tasks to it
exc.register_subscriber(task_a)
exc.register_subscriber(task_b)

# Example of publish messages
exc.publish('msg1')
exc.publish('msg2')

# Example of unsubscribing
exc.unsubscribe(task_a)
exc.unsubscribe(task_b)
