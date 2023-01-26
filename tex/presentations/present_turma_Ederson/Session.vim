let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/repos/Sun_Fields/tex/presentations/present_turma_Ederson
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
argglobal
%argdel
$argadd apresentacao.tex
edit apresentacao.tex
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=2
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
17,23fold
30,54fold
58,70fold
72,85fold
89,102fold
104,118fold
122,139fold
141,161fold
141,161fold
165,182fold
165,182fold
186,199fold
201,215fold
217,230fold
232,245fold
184,245fold
251,256fold
258,277fold
281,305fold
309,351fold
353,377fold
379,403fold
405,428fold
430,453fold
309,453fold
457,464fold
466,473fold
475,482fold
475,482fold
484,491fold
493,500fold
502,509fold
511,518fold
520,527fold
529,536fold
538,545fold
547,554fold
556,563fold
457,563fold
567,580fold
let &fdl = &fdl
17
normal! zc
30
normal! zc
58
normal! zc
72
normal! zc
89
normal! zc
104
normal! zc
122
normal! zc
141
normal! zo
141
normal! zc
165
normal! zo
165
normal! zc
184
normal! zo
186
normal! zc
201
normal! zc
217
normal! zc
232
normal! zc
184
normal! zc
251
normal! zc
258
normal! zc
281
normal! zc
309
normal! zo
309
normal! zc
353
normal! zc
379
normal! zc
405
normal! zc
430
normal! zc
457
normal! zo
457
normal! zc
466
normal! zc
475
normal! zo
484
normal! zc
493
normal! zc
502
normal! zc
511
normal! zc
520
normal! zc
529
normal! zc
538
normal! zc
547
normal! zc
556
normal! zc
457
normal! zc
567
normal! zc
let s:l = 581 - ((333 * winheight(0) + 16) / 32)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 581
normal! 0
tabnext 1
badd +482 apresentacao.tex
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOF
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
