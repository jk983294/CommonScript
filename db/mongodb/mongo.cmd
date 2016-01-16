"C:\Program Files\MongoDB\Server\3.2\bin\mongod.exe" --config "E:\GitHub\CommonScript\db\mongodb\mongod.cfg" --install
net start MongoDB
net stop MongoDB
"C:\Program Files\MongoDB\Server\3.2\bin\mongod.exe" --remove



sc.exe create MongoDB binPath= "C:\Program Files\MongoDB\Server\3.2\bin\mongod.exe --service --config=\"E:\GitHub\CommonScript\db\mongodb\mongod.cfg\"" DisplayName= "MongoDB" start= "auto"
net start MongoDB
net stop MongoDB
sc.exe delete MongoDB