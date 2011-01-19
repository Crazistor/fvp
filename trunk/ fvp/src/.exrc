if &cp | set nocp | endif
nmap  :BottomExplorerWindow
nmap  :FirstExplorerWindow
vmap [% [%m'gv``
let s:cpo_save=&cpo
set cpo&vim
map \mbt <Plug>TMiniBufExplorer
map \mbu <Plug>UMiniBufExplorer
map \mbc <Plug>CMiniBufExplorer
map \mbe <Plug>MiniBufExplorer
nmap \ihn :IHN
nmap \is :IHS:A
nmap \ih :IHS
nmap <silent> \wm :WMToggle
vmap ]% ]%m'gv``
vmap a% [%v]%
nmap gx <Plug>NetrwBrowseX
map <silent> mm <Plug>Vm_toggle_sign 
nmap wm :WMToggle
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetBrowseX(expand("<cWORD>"),0)
map <S-F2> <Plug>Vm_goto_prev_sign
map <F2> <Plug>Vm_goto_next_sign
map <C-F2> <Plug>Vm_toggle_sign
noremap <C-Right> l
noremap <C-Left> h
noremap <C-Up> k
noremap <C-Down> j
imap \ihn :IHN
imap \is :IHS:A
imap \ih :IHS
let &cpo=s:cpo_save
unlet s:cpo_save
set background=dark
set backspace=indent,eol,start
set cscopeprg=/usr/bin/cscope
set cscopetag
set noequalalways
set fileencodings=ucs-bom,utf-8,latin1
set formatoptions=tcql
set guicursor=n-v-c:block,o:hor50,i-ci:hor15,r-cr:hor30,sm:block,a:blinkon0
set helplang=en
set history=50
set hlsearch
set nomodeline
set ruler
set tabstop=4
set viminfo='20,\"50
" vim: set ft=vim :
