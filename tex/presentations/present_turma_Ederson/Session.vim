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
109,118fold
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
251,257fold
259,278fold
282,306fold
310,352fold
354,378fold
380,404fold
406,429fold
309,453fold
309,454fold
458,465fold
467,474fold
476,483fold
475,483fold
485,492fold
494,501fold
503,510fold
512,519fold
521,528fold
530,537fold
539,546fold
548,555fold
557,564fold
458,564fold
568,581fold
585,602fold
606,614fold
619,622fold
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
normal! zo
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
259
normal! zc
282
normal! zc
309
normal! zo
309
normal! zo
309
normal! zc
458
normal! zo
458
normal! zc
467
normal! zc
475
normal! zo
485
normal! zc
494
normal! zc
503
normal! zc
512
normal! zc
521
normal! zc
530
normal! zc
539
normal! zc
548
normal! zc
557
normal! zc
458
normal! zc
568
normal! zc
585
normal! zc
606
normal! zc
619
normal! zc
let s:l = 623 - ((344 * winheight(0) + 16) / 32)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 623
normal! 0
tabnext 1
badd +619 apresentacao.tex
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
