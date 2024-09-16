let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Projects/BTech/ESP32_MeshNet_For_Node_To_Gateway_Communication/src/station
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +0 station.ino
badd +13 website.cpp
badd +22 website.h
badd +1 wifi_config.cpp
badd +16 wifi_config.h
argglobal
%argdel
$argadd config.h
$argadd humid_temp_sensor.cpp
$argadd humid_temp_sensor.h
$argadd light_sensor.cpp
$argadd light_sensor.h
$argadd Monitor.cpp
$argadd Monitor.h
$argadd pins.h
$argadd station.ino
$argadd weather_station.cpp
$argadd weather_station.h
$argadd website.cpp
$argadd website.h
$argadd wifi_config.cpp
$argadd wifi_config.h
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit website.h
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 84 + 85) / 170)
exe '2resize ' . ((&lines * 29 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 85 + 85) / 170)
exe '3resize ' . ((&lines * 10 + 21) / 42)
exe 'vert 3resize ' . ((&columns * 85 + 85) / 170)
argglobal
if bufexists(fnamemodify("website.h", ":p")) | buffer website.h | else | edit website.h | endif
if &buftype ==# 'terminal'
  silent file website.h
endif
balt wifi_config.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
11,12fold
13,20fold
let &fdl = &fdl
let s:l = 22 - ((21 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 22
normal! 023|
wincmd w
argglobal
if bufexists(fnamemodify("website.cpp", ":p")) | buffer website.cpp | else | edit website.cpp | endif
if &buftype ==# 'terminal'
  silent file website.cpp
endif
balt website.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
31,58fold
66,67fold
70,71fold
83,84fold
99,100fold
102,103fold
105,106fold
108,109fold
111,112fold
114,115fold
117,118fold
59,129fold
30,130fold
131,132fold
29,133fold
134,135fold
25,136fold
23,137fold
17,138fold
15,139fold
let &fdl = &fdl
let s:l = 28 - ((4 * winheight(0) + 14) / 28)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 28
normal! 020|
wincmd w
argglobal
enew
balt website.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
wincmd w
exe 'vert 1resize ' . ((&columns * 84 + 85) / 170)
exe '2resize ' . ((&lines * 29 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 85 + 85) / 170)
exe '3resize ' . ((&lines * 10 + 21) / 42)
exe 'vert 3resize ' . ((&columns * 85 + 85) / 170)
tabnext
edit website.h
argglobal
balt wifi_config.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
11,12fold
13,20fold
let &fdl = &fdl
let s:l = 22 - ((9 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 22
normal! 023|
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
