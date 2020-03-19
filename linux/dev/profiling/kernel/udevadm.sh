# udevadm listens to kernel uevents
# 监控设备事件
udevadm monitor --property                                  # 输出事件的属性
udevadm monitor --kernel --property --subsystem-match=usb   # 过滤监听符合条件的时间
# available options:
--kernel　　                输出内核事件
--udev　　                  输出udev规则执行时的udev事件
--property　　              输出事件的属性
--subsystem-match=string　　通过子系统或者设备类型过滤事件。只有匹配了子系统值的udev设备事件通过。
--tag-match=string　　      通过属性过滤事件，只有匹配了标签的udev事件通过。

# 查看设备信息
udevadm info --query=all --name=sda         # 查询sda的所有信息
udevadm info --query=path --name=sda        # 查看sda的path
# available options:
# --query=type                  从数据库中查询指定类型的设备。需要--path和--name来指定设备。合法的查询文件是：设备名，链接，路径，属性
# --path=devpath                设备的路径
# --name=file                   设备节点或者链接
# --attribute-walk              打印指定设备的所有sysfs记录的属性，以用来udev规则匹配特殊的设备。该选项打印链上的所有设备信息，最大可能到sys目录。
# --device-id-of-file=file      打印主/从设备号
# --export-db                   输出udev数据库中的内容