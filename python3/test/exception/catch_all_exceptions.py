try:
    pass
except Exception as e:          # capture all except SystemExit, KeyboardInterrupt, GeneratorExit
    print('Reason:', e)


try:
    pass
except BaseException as e:      # capture all include SystemExit, KeyboardInterrupt, GeneratorExit
    print('Reason:', e)


