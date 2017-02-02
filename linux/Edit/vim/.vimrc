set nocompatible

" Vim5 and later versions support syntax highlighting. Uncommenting the
" following enables syntax highlighting by default.
if has("syntax")
  syntax on            " �﷨����
endif
colorscheme ron        " elflord ron peachpuff default ������ɫ������vim�Դ�����ɫ����������/usr/share/vim/vim72/colorsĿ¼��

" nmap
nmap <C-N> :set invnumber<CR>


" detect file type
filetype on
filetype plugin on

" If using a dark background within the editing area and syntax highlighting
" turn on this option as well
set background=dark

" Uncomment the following to have Vim jump to the last position when
" reopening a file
if has("autocmd")
  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
  "have Vim load indentation rules and plugins according to the detected filetype
  filetype plugin indent on
endif

" The following are commented out as they cause vim to behave a lot
" differently from regular Vi. They are highly recommended though.

"set ignorecase         " ����ģʽ����Դ�Сд
"set smartcase          " �������ģʽ������д�ַ�����ʹ�� 'ignorecase' ѡ�ֻ������������ģʽ���Ҵ� 'ignorecase' ѡ��ʱ�Ż�ʹ�á�
set autowrite           " �Զ�������д���ļ�: ����ļ����޸Ĺ�����ÿ�� :next��:rewind��:last��:first��:previous��:stop��:suspend��:tag��:!��:make��CTRL-] �� CTRL-^����ʱ���У��� :buffer��CTRL-O��CTRL-I��'{A-Z0-9} �� `{A-Z0-9} ����ת������ļ�ʱ��Ȼ��
set autoindent          " �����Զ�����(����)����ÿ�е�����ֵ����һ����ȣ�ʹ�� noautoindent ȡ������
"set smartindent        " ���ܶ��뷽ʽ
set tabstop=4           " �����Ʊ��(tab��)�Ŀ��
set softtabstop=4       " �������Ʊ���Ŀ��
set shiftwidth=4        " (�Զ�) ����ʹ�õ�4���ո�
set cindent             " ʹ�� C/C++ ���Ե��Զ�������ʽ
set cinoptions={0,1s,t0,n-2,p2s,(03s,=.5s,>1s,=1s,:1s       " ����C/C++���Եľ���������ʽ
"set backspace=2        " �����˸������
set showmatch           " ����ƥ��ģʽ����ʾƥ�������
set linebreak           " ���ʻ���
set whichwrap=b,s,<,>,[,]   " �������׺���ĩʱ����������һ��ȥ
"set hidden " Hide buffers when they are abandoned
set mouse=a             " Enable mouse usage (all modes)    "ʹ�����
set number              " Enable line number    "��ʾ�к�
"set previewwindow      " ��ʶԤ������
set history=50          " set command history to 50    "��ʷ��¼50��


"--״̬������--
set laststatus=2        " ����ʾ���һ�����ڵ�״̬�У���Ϊ1�򴰿�������һ����ʱ����ʾ���һ�����ڵ�״̬�У�0����ʾ���һ�����ڵ�״̬��
set ruler               " ��ߣ�������ʾ���λ�õ��кź��кţ����ŷָ���ÿ�����ڶ����Լ��ı�ߡ����������״̬�У������������ʾ����������ʾ����Ļ�����һ���ϡ�

"--����������--
set showcmd             " ��������ʾ���������
set showmode            " ��������ʾvim��ǰģʽ

"--find setting--
set incsearch           " �����ַ�������ʾƥ���
set hlsearch

"-- omnicppcomplete setting --
set completeopt=menu,menuone        " �ص����ܲ�ȫʱ��Ԥ������
let OmniCpp_MayCompleteDot = 1      " autocomplete with .
let OmniCpp_MayCompleteArrow = 1    " autocomplete with ->
let OmniCpp_MayCompleteScope = 1    " autocomplete with ::
let OmniCpp_SelectFirstItem = 2     " select first item (but don't insert)
let OmniCpp_NamespaceSearch = 2     " search namespaces in this and included files
let OmniCpp_ShowPrototypeInAbbr = 1 " show function prototype in popup window
let OmniCpp_GlobalScopeSearch=1     " enable the global scope search
let OmniCpp_DisplayMode=1           " Class scope completion mode: always show all members
"let OmniCpp_DefaultNamespaces=["std"]
let OmniCpp_ShowScopeInAbbr=1       " show scope in abbreviation and remove the last column
let OmniCpp_ShowAccess=1