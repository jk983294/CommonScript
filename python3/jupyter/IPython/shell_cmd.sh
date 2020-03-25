# shell commands
!ls
!pwd
!!ls                # cannot capture result with !!

# capture result
files = !ls
files = %sx ls
dir_path_to_ls = '/opt/'
files = !ls $dir_path_to_ls
!echo "A python variable: {dir_path_to_ls}"

# aliases
%alias parts echo first %s second %s
parts A B