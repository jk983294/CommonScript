# using list as queue
queue = ['Eric', 'John', 'Michael']
queue.append('Terry')                       # Terry arrives
queue.append('Graham')                      # Graham arrives
queue.pop(0)                                # 'Eric', ['John', 'Michael', 'Terry', 'Graham']
queue.pop(0)                                # 'John', ['Michael', 'Terry', 'Graham']
