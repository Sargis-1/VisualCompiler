#include "bss.h"

Bss::Bss() : AbsRam(Segment::Bss, 0xE666665D, 0xE666665D) { //Initializing Starting and current addresses of this Segment

}

Bss::~Bss() noexcept {

}

//   Adress distribution among all Ram Segments
//     //0000 0000 - 5999 9994  - 35%
//     //5999 9995 - B333 332A  - 35%
//     //B333 332B - CCCC CCC3  - 10%
//     //CCCC CCC4 - E666 665C  - 10%
//     //E666 665D _ FFFF FFFF  - 10%
