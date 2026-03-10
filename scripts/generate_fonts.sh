
function generate_font() {
  font_file=$1
  font_size=$2
  font_name=$3
  font_postfix=$4

  python scripts/generate_simplefont/cli.py --name Bookerly$font_size$font_postfix --size $font_size --chars-file resources/chars_input.txt --ttf resources/fonts/$font_file --out src/resources/fonts/bookerly/$font_name$font_size$font_postfix.h
}


generate_font Bookerly.ttf 26 Bookerly 
generate_font Bookerly.ttf 28 Bookerly 
generate_font Bookerly.ttf 30 Bookerly 

generate_font Bookerly-Italic.ttf 26 Bookerly Italic
generate_font Bookerly-Italic.ttf 28 Bookerly Italic
generate_font Bookerly-Italic.ttf 30 Bookerly Italic

generate_font Bookerly-Bold.ttf 26 Bookerly Bold
generate_font Bookerly-Bold.ttf 28 Bookerly Bold
generate_font Bookerly-Bold.ttf 30 Bookerly Bold

generate_font Bookerly-Bold-Italic.ttf 26 Bookerly BoldItalic
generate_font Bookerly-Bold-Italic.ttf 28 Bookerly BoldItalic
generate_font Bookerly-Bold-Italic.ttf 30 Bookerly BoldItalic
