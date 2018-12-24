# three area: working directory -> staging index -> repository

# commit 引用
    ^                               – 表示父 commit
    ~                               – 表示第一个父 commit
    parent commit                   – 以下内容表示当前 commit 的父 commit
    HEAD^
    HEAD~
    HEAD~1
    grandfather commit              – 以下内容表示当前 commit 的祖父 commit
    HEAD^^
    HEAD~2
    grand-grandfather commit        – 以下内容表示当前 commit 的曾祖父 commit
    HEAD^^^
    HEAD~3
^ 和 ~ 的区别主要体现在通过合并而创建的 commit 中。合并 commit 具有两个父级。
对于合并 commit，^ 引用用来表示第一个父 commit，而 ^2 表示第二个父 commit。
第一个父 commit 是当你运行 git merge 时所处的分支，而第二个父 commit 是被合并的分支。
Example:
* 9ec05ca (HEAD -> master) Revert "Set page heading to "Quests & Crusades""
* db7e87a Set page heading to "Quests & Crusades"
*   796ddb0 Merge branch 'heading-update'
|\
| * 4c9749e (heading-update) Set page heading to "Crusade"
* | 0c5975a Set page heading to "Quest"
|/
*   1a56a81 Merge branch 'sidebar'

因为 HEAD 指向 9ec05ca commit：
HEAD^ 是 db7e87a commit
HEAD~1 同样是 db7e87a commit
HEAD^^ 是 796ddb0 commit
HEAD~2 同样是 796ddb0 commit
HEAD^^^ 是 0c5975a commit
HEAD~3 同样是 0c5975a commit
HEAD^^^2 是 4c9749e commit（这是曾祖父的 (HEAD^^) 第二个父 commit (^2))

# git reset commit, 将 HEAD 和当前分支指针移到引用的 commit, default --mixed
git reset --mixed HEAD~1            # move current HEAD to working directory
git reset --soft HEAD~1             # move current HEAD to staging index
git reset --hard HEAD~1             # delete current HEAD


# branch
HEAD point to one branch
when you commit, the HEAD branch moves on
checkout command makes HEAD point to specified branch

# merge
快进合并（Fast-forward merge）。快进合并将使当前检出的分支向前移动，直到它指向与另一个分支指向的commit一样为止

# 合并冲突
完全相同的行在不同的文件中更改了，将产生合并冲突
git将尝试尽可能合并多的内容，然后将留下特殊选项，告诉你需要从何处手动修复

<<<<<<< HEAD                                    # 此行下方的所有内容（直到下个指示符）显示了当前分支上的行
        <h1>Expedition test2</h1>
||||||| merged common ancestors                 # 此行下方的所有内容（直到下个指示符）显示了原始行的内容
        <h1>Expedition</h1>
=======                                         # 表示原始行内容的结束位置，之后的所有行（直到下个指示符）是被合并的当前分支上的行的内容
        <h1>Expedition test1</h1>
>>>>>>> conflict_test                           # 要被合并的分支（此例中是 conflict_test 分支）上的行结束指示符


# repository
git init

$ tree
   .
   |-config                 # git configs
   |-description            # used by GitWeb
   |-HEAD
   |-branches
   |-hooks                  # 放置客户端或服务器端脚本，以便用来连接到 Git 的不同生命周期事件
   |-info                   # 包含全局排除文件
   |-objects                # 此目录将存储我们提交的所有 commit
   |---info
   |---pack
   |-refs                   # 此目录存储了指向 commit 的指针（通常是“分支”和“标签”）
   |---heads
   |---tags

# git patch
diff --git a/css/app.css b/css/app.css      # file rename to another file
index 07c36fa..3cbd0b8 100644               # 文件第一版的哈希值和第二版的哈希值
--- a/css/app.css                           # 文件的旧版本和当前版本
+++ b/css/app.css
@@ -38,6 +38,11 @@ p {                      # first file show from 38 line, 6 line showed, second one show from 38 line, 11 lines showed (6 old one with 5 addition)
     line-height: 1.5;
 }

+.container {                               # 用红色标示并以减号 (-) 开头的行是位于文件原始版本中，但是被 commit 删除的行
+    margin: auto;                          # 用绿色标示并以加号 (+) 开头的行是 commit 新加的行
+    max-width: 1300px;
+}
+

 /*** Header Styling ***/
 .page-header {
