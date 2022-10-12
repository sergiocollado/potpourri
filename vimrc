
" ref: https://gist.github.com/sushantmane/ab6901696bf93f790ef3
set nu
filetype plugin indent on
syn on se title
set tabstop=8
set softtabstop=8
set shiftwidth=8
set noexpandtab
set list listchars=tab:»\ ,trail:.,extends:»,precedes:«
set ai

" ref: https://stackoverflow.com/questions/33676829/vim-configuration-for-linux-kernel-development

" 80 characters line
set colorcolumn=81
"execute "set colorcolumn=" . join(range(81,335), ',')
highlight ColorColumn ctermbg=Black ctermfg=DarkRed


" Highlight trailing spaces
" http://vim.wikia.com/wiki/Highlight_unwanted_spaces
highlight ExtraWhitespace ctermbg=red guibg=red
match ExtraWhitespace /\s\+$/
autocmd BufWinEnter * match ExtraWhitespace /\s\+$/
autocmd InsertEnter * match ExtraWhitespace /\s\+\%#\@<!$/
autocmd InsertLeave * match ExtraWhitespace /\s\+$/
autocmd BufWinLeave * call clearmatches()
