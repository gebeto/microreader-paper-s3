
function generate_font() {
  font_file=$1
  font_size=$2
  font_folder=$3
  font_name=$4
  font_postfix=$5

  python scripts/generate_simplefont/cli.py --name Bookerly$font_size$font_postfix --size $font_size --chars-file resources/chars_input.txt --ttf resources/fonts/$font_file --out src/resources/fonts/$font_folder/$font_name$font_size$font_postfix.h
}


generate_font Bookerly.ttf 26 bookerly Bookerly
generate_font Bookerly.ttf 28 bookerly Bookerly
generate_font Bookerly.ttf 30 bookerly Bookerly

generate_font Bookerly-Italic.ttf 26 bookerly Bookerly Italic
generate_font Bookerly-Italic.ttf 28 bookerly Bookerly Italic
generate_font Bookerly-Italic.ttf 30 bookerly Bookerly Italic

generate_font Bookerly-Bold.ttf 26 bookerly Bookerly Bold
generate_font Bookerly-Bold.ttf 28 bookerly Bookerly Bold
generate_font Bookerly-Bold.ttf 30 bookerly Bookerly Bold

generate_font Bookerly-Bold-Italic.ttf 26 bookerly Bookerly BoldItalic
generate_font Bookerly-Bold-Italic.ttf 28 bookerly Bookerly BoldItalic
generate_font Bookerly-Bold-Italic.ttf 30 bookerly Bookerly BoldItalic

python scripts/generate_simplefont/cli.py --name MenuFontSmall --size 10 --chars-file resources/chars_input.txt --ttf resources/fonts/RobotoMono-SemiBold.ttf --out src/resources/fonts/other/MenuFontSmall.h
python scripts/generate_simplefont/cli.py --name MenuFontBig --size 20 --chars-file resources/chars_input.txt --ttf resources/fonts/RobotoMono-SemiBold.ttf --out src/resources/fonts/other/MenuFontBig.h
