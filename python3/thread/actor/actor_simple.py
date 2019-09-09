import learn.thread.actor.actor_base as ActorBase


# Sample ActorTask
class PrintActor(ActorBase.Actor):
    def run(self):
        while True:
            msg = self.recv()
            print('Got:', msg)


# Sample use
p = PrintActor()
p.start()
p.send('Hello')
p.send('World')
p.close()
p.join()
