//
// created by serge lussier on 2025-09-30.
//



////////////////////////////////////////////////////////////////////////////////////////////
//   copyright (c) ...,2025,... by serge lussier
//   serge.lussier@oldbitsnbytes.club / lussier.serge@gmail.com
//   ----------------------------------------------------------------------------------
//   unless otherwise specified, all codes and files in this project is written
//   by the author and owned by the author (serge lussier), unless otherwise specified.
//   ----------------------------------------------------------------------------------
//   copyrights from authors other than serge lussier also apply here.
//   open source free licences also apply to the code from the author (serge lussier)
//   ----------------------------------------------------------------------------------
//   usual gnu free gpl-1,2, mit... or whatever -  apply to this project.
//   ----------------------------------------------------------------------------------
//   note : all source code that i am the only author, i reserve for myself, the rights to
//   make it to restricted private license.
////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------------

#include "catui/io/kstroke.h"

#include <catui/io/kstroke.h>

namespace cat::io
{

kstroke kstroke::none{kstroke::NO_KEY, 0};




kstroke::kstroke(kstroke::enums e, u64 c): mnemonic(e), kcode(c){}





kstroke::dbgroup kstroke::keysdb
{
    {kstroke::ARROW_UP              ,0x00000000001b5b41},
    {kstroke::ARROW_DOWN            ,0x00000000001b5b42},
    {kstroke::ARROW_LEFT            ,0x00000000001b5b44},
    {kstroke::ARROW_RIGHT           ,0x00000000001b5b43},
    {kstroke::ENTER                 ,0x000000000000000a},
    {kstroke::ESCAPE                ,0x000000000000001b},
    {kstroke::BACKSPACE             ,0x000000000000007f},
    {kstroke::HOME                  ,0x00000000001b5b48},
    {kstroke::END                   ,0x00000000001b5b46},
    {kstroke::PAGE_UP               ,0x000000001b5b357e},
    {kstroke::PAGE_DOWN             ,0x000000001b5b367e},
    {kstroke::INSERT                ,0x000000001b5b327e},
    {kstroke::DELETE                ,0x000000001b5b337e},
    {kstroke::TAB                   ,0x0000000000000009},
    {kstroke::F1                    ,0x00000000001b4f50},
    {kstroke::F2                    ,0x00000000001b4f51},
    {kstroke::F3                    ,0x00000000001b4f52},
    {kstroke::F4                    ,0x00000000001b4f53},
    {kstroke::F5                    ,0x0000001b5b31357e},
    {kstroke::F6                    ,0x0000001b5b31377e},
    {kstroke::F7                    ,0x0000001b5b31387e},
    {kstroke::F8                    ,0x0000001b5b31397e},
    {kstroke::F9                    ,0x0000001b5b32307e},
    {kstroke::F10                   ,0x0000001b5b32317e},
    {kstroke::F11                   ,0x0000001b5b32337e},
    {kstroke::F12                   ,0x0000001b5b32347e},
    {kstroke::SHIFT_ARROW_UP        ,0x00001b5b313b3241},
    {kstroke::SHIFT_ARROW_DOWN      ,0x00001b5b313b3242},
    {kstroke::SHIFT_ARROW_LEFT      ,0x00001b5b313b3244},
    {kstroke::SHIFT_ARROW_RIGHT     ,0x00001b5b313b3243},
    {kstroke::SHIFT_END             ,0x00001b5b313b3246},
    {kstroke::SHIFT_HOME            ,0x00001b5b313b3248},
    {kstroke::SHIFT_PAGE_UP         ,0x00001b5b353b327e},
    {kstroke::SHIFT_PAGE_DOWN       ,0x00001b5b363b327e},
    {kstroke::SHIFT_F1              ,0x000000001b4f3250},
    {kstroke::SHIFT_F2              ,0x000000001b4f3251},
    {kstroke::SHIFT_F3              ,0x000000001b4f3252},
    {kstroke::SHIFT_F4              ,0x000000001b4f3253},
    {kstroke::SHIFT_F5              ,0x001b5b31353b327e},
    {kstroke::SHIFT_F6              ,0x001b5b31373b327e},
    {kstroke::SHIFT_F7              ,0x001b5b31383b327e},
    {kstroke::SHIFT_F8              ,0x001b5b31393b327e},
    {kstroke::SHIFT_F9              ,0x001b5b32303b327e},
    {kstroke::SHIFT_F10             ,0x001b5b32313b327e},
    {kstroke::SHIFT_F11             ,0x001b5b32333b327e},
    {kstroke::SHIFT_F12             ,0x001b5b32343b327e},
    {kstroke::SHIFT_TAB             ,0x00000000001b5b5a},
    {kstroke::SHIFT_ENTER           ,0x00000000001b4f4d},
    {kstroke::CTRL_PAGE_UP          ,0x00001b5b353b357e},
    {kstroke::CTRL_PAGE_DOWN        ,0x00001b5b363b357e},
    {kstroke::CTRL_DELETE           ,0x00001b5b333b357e},
    {kstroke::CTRL_END              ,0x00001b5b313b3546},
    {kstroke::CTRL_ARROW_LEFT       ,0x00001b5b313b3544},
    {kstroke::CTRL_ARROW_RIGHT      ,0x00001b5b313b3543},
    {kstroke::CTRL_ARROW_UP         ,0x00001b5b313b3541},
    {kstroke::CTRL_ARROW_DOWN       ,0x00001b5b313b3542},
    {kstroke::CTRL_HOME             ,0x00001b5b313b3548},
    {kstroke::CTRL_INSERT           ,0x00001b5b323b357e},
    {kstroke::CTRL_Q                ,0x0000000000000011},
    {kstroke::CTRL_S                ,0x0000000000000013},
    {kstroke::CTRL_V                ,0x0000000000000016},
    {kstroke::CTRL_BACKSPACE        ,0x0000000000000008},
    {kstroke::CTRL_F8               ,0x001b5b31393b357e},
    {kstroke::ALT_ARROW_LEFT        ,0x00001b5b313b3344},
    {kstroke::ALT_ARROW_RIGHT       ,0x00001b5b313b3343},
    {kstroke::ALT_ARROW_UP          ,0x00001b5b313b3341},
    {kstroke::ALT_ARROW_DOWN        ,0x00001b5b313b3342},
    {kstroke::SHIFT_CTRL_ARROW_LEFT ,0x00001b5b313b3644},
    {kstroke::SHIFT_CTRL_ARROW_RIGHT,0x00001b5b313b3643},
    {kstroke::SHIFT_CTRL_ARROW_UP   ,0x00001b5b313b3641},
    {kstroke::SHIFT_CTRL_ARROW_DOWN ,0x00001b5b313b3642},
    {kstroke::SHIFT_CTRL_DEL        ,0x00001b5b313b3646},
    {kstroke::SHIFT_CTRL_HOME       ,0x00001b5b313b3648},
    {kstroke::SHIFT_ALT_ARROW_LEFT  ,0x00001b5b313b3444},
    {kstroke::SHIFT_ALT_ARROW_RIGHT ,0x00001b5b313b3443},
    {kstroke::SHIFT_ALT_ARROW_UP    ,0x00001b5b313b3441},
    {kstroke::SHIFT_ALT_ARROW_DOWN  ,0x00001b5b313b3442},
    {kstroke::SHIFT_ALT_END         ,0x00001b5b313b3446},
    {kstroke::SHIFT_ALT_HOME        ,0x00001b5b313b3448},
    {kstroke::SHIFT_ALT_PAGE_UP     ,0x00001b5b353b347e},
    {kstroke::SHIFT_ALT_PAGE_DOWN   ,0x00001b5b363b347e},
    {kstroke::CTRL_ALT_ARROW_LEFT   ,0x00001b5b313b3744},
    {kstroke::CTRL_ALT_ARROW_RIGHT  ,0x00001b5b313b3743},
    {kstroke::CTRL_ALT_ARROW_UP     ,0x00001b5b313b3741},
    {kstroke::CTRL_ALT_ARROW_DOWN   ,0x00001b5b313b3742},
    {kstroke::CHARACTER             ,0x0000000000000000}, ///< never hit.


    //...
};


std::map<kstroke::enums, const char*> key_names={
{kstroke::ARROW_UP              ,"arrowup"               },
{kstroke::ARROW_DOWN            ,"arrowdown"             },
{kstroke::ARROW_LEFT            ,"arrowleft"             },
{kstroke::ARROW_RIGHT           ,"arrowright"            },
{kstroke::ENTER                 ,"enter"                 },
{kstroke::ESCAPE                ,"escape/cancel/dismiss" },
{kstroke::BACKSPACE             ,"backspace"             },
{kstroke::HOME                  ,"home"                  },
{kstroke::END                   ,"end"                   },
{kstroke::PAGE_UP               ,"pageup"                },
{kstroke::PAGE_DOWN             ,"pagedown"              },
{kstroke::INSERT                ,"insert"                },
{kstroke::DELETE                ,"delete"                },
{kstroke::TAB                   ,"tab"                   },
{kstroke::F1                    ,"f1"                    },
{kstroke::F2                    ,"f2"                    },
{kstroke::F3                    ,"f3"                    },
{kstroke::F4                    ,"f4"                    },
{kstroke::F5                    ,"f5"                    },
{kstroke::F6                    ,"f6"                    },
{kstroke::F7                    ,"f7"                    },
{kstroke::F8                    ,"f8"                    },
{kstroke::F9                    ,"f9"                    },
{kstroke::F10                   ,"f10"                   },
{kstroke::F11                   ,"f11"                   },
{kstroke::F12                   ,"f12"                   },
{kstroke::SHIFT_ARROW_UP        ,"shift+arrowup"         },
{kstroke::SHIFT_ARROW_DOWN      ,"shift+arrowdown"       },
{kstroke::SHIFT_ARROW_LEFT      ,"shift+arrowleft"       },
{kstroke::SHIFT_ARROW_RIGHT     ,"shift+arrowright"      },
{kstroke::SHIFT_END             ,"shift+end"             },
{kstroke::SHIFT_HOME            ,"shift+home"            },
{kstroke::SHIFT_PAGE_UP         ,"shift+pageup"          },
{kstroke::SHIFT_PAGE_DOWN       ,"shift+pagedown"        },
{kstroke::SHIFT_F1              ,"shift+f1"              },
{kstroke::SHIFT_F2              ,"shift+f2"              },
{kstroke::SHIFT_F3              ,"shift+f3"              },
{kstroke::SHIFT_F4              ,"shift+f4"              },
{kstroke::SHIFT_F5              ,"shift+f5"              },
{kstroke::SHIFT_F6              ,"shift+f6"              },
{kstroke::SHIFT_F7              ,"shift+f7"              },
{kstroke::SHIFT_F8              ,"shift+f8"              },
{kstroke::SHIFT_F9              ,"shift+f9"              },
{kstroke::SHIFT_F10             ,"shift+f10"             },
{kstroke::SHIFT_F11             ,"shift+f11"             },
{kstroke::SHIFT_F12             ,"shift+f12"             },
{kstroke::SHIFT_TAB             ,"shift+tab"             },
{kstroke::SHIFT_ENTER           ,"shift+enter"           },
{kstroke::CTRL_PAGE_UP          ,"ctrl+pageup"           },
{kstroke::CTRL_PAGE_DOWN        ,"ctrl+pagedown"         },
{kstroke::CTRL_DELETE           ,"ctrl+delete"           },
{kstroke::CTRL_END              ,"ctrl+end"              },
{kstroke::CTRL_ARROW_LEFT       ,"ctrl+arrowleft"        },
{kstroke::CTRL_ARROW_RIGHT      ,"ctrl+arrowright"       },
{kstroke::CTRL_ARROW_UP         ,"ctrl+arrowup"          },
{kstroke::CTRL_ARROW_DOWN       ,"ctrl+arrowdown"        },
{kstroke::CTRL_HOME             ,"ctrl+home"             },
{kstroke::CTRL_INSERT           ,"ctrl+insert"           },
{kstroke::CTRL_Q                ,"ctrl+q"                },
{kstroke::CTRL_S                ,"ctrl+s"                },
{kstroke::CTRL_V                ,"ctrl+v"                },
{kstroke::CTRL_BACKSPACE        ,"ctrl+back-space"       },
{kstroke::CTRL_F8               ,"ctrl+f8"               },
{kstroke::ALT_ARROW_LEFT        ,"alt+arrowleft"         },
{kstroke::ALT_ARROW_RIGHT       ,"alt+arrowright"        },
{kstroke::ALT_ARROW_UP          ,"alt+arrowup"           },
{kstroke::ALT_ARROW_DOWN        ,"alt+arrowdown"         },
{kstroke::SHIFT_CTRL_ARROW_LEFT ,"shift+ctrl+arrowleft"  },
{kstroke::SHIFT_CTRL_ARROW_RIGHT,"shift+ctrl+arrowright" },
{kstroke::SHIFT_CTRL_ARROW_UP   ,"shift+ctrl+arrowup"    },
{kstroke::SHIFT_CTRL_ARROW_DOWN ,"shift+ctrl+arrowdown"  },
{kstroke::SHIFT_CTRL_DEL        ,"shift+ctrl+del"        },
{kstroke::SHIFT_CTRL_HOME       ,"shift+ctrl+home"       },
{kstroke::SHIFT_ALT_ARROW_LEFT  ,"shift+alt+arrowleft"   },
{kstroke::SHIFT_ALT_ARROW_RIGHT ,"shift+alt+arrowright"  },
{kstroke::SHIFT_ALT_ARROW_UP    ,"shift+alt+arrowup"     },
{kstroke::SHIFT_ALT_ARROW_DOWN  ,"shift+alt+arrowdown"   },
{kstroke::SHIFT_ALT_END         ,"shift+alt+end"         },
{kstroke::SHIFT_ALT_HOME        ,"shift+alt+home"        },
{kstroke::SHIFT_ALT_PAGE_UP     ,"shift+alt+pageup"      },
{kstroke::SHIFT_ALT_PAGE_DOWN   ,"shift+alt+pagedown"    },
{kstroke::CTRL_ALT_ARROW_LEFT   ,"ctrl+alt+arrowleft"    },
{kstroke::CTRL_ALT_ARROW_RIGHT  ,"ctrl+alt+arrowright"   },
{kstroke::CTRL_ALT_ARROW_UP     ,"ctrl+alt+arrowup"      },
{kstroke::CTRL_ALT_ARROW_DOWN   ,"ctrl+alt+arrowdown"    },
{kstroke::CHARACTER             ,"char input"            }
};


kstroke kstroke::query(u64 code_seq)
{
    for (auto const &k : kstroke::keysdb)
        if (k.kcode == code_seq) return k;
    return none;
}


kstroke kstroke::query(std::string_view s)
{
    for (auto [k,v] : key_names)
        if ( v == s)
                return kstroke::keysdb[k];
    return none;
}


/////////////////////////////////////////////////////////////////////////////
/// \brief keyinput::test
/// \param fd
/// \return
/// \note requires that the first byte in _fd must not be consumed.
/// attention! modify the code that pull and analyses bytes from the input buffer. it was ancient code and the new buffer code does not work the same now...
/// right now i am re-writing into the buffer !!! lol!! doh!!
 std::pair<rem::code, kstroke>  kstroke::parse(pollin &fd)
{

    auto log = sys::debug();
    log << color::yellow << fd.buffer.size() <<  color::r << " bytes waiting." << log;
    auto str = cat::string::bytes(fd.buffer);
    log << color::lime << str << color::z << log;
    auto byte = fd.buffer.begin();
    u64 code = *byte;
    kstroke kb{};
    if(fd.buffer.size() == 1){
        if(kb = kstroke::query(code); !kb){
            kb.mnemonic = kstroke::CHARACTER;
            kb.kcode = code;
        }

        return {rem::code::ready,kb};
    }
    if(code==0x1b) // csi start
    {
        auto n = std::min(static_cast<u64>(7),static_cast<u64>(byte - fd.buffer.begin()));
        ++byte;
        // csi
        do{
            code = code << 8 | *byte++;
            if(kb = kstroke::query(code); kb.mnemonic != kstroke::NO_KEY)
            {
                return {rem::code::ready,kb};
            }
            --n;
            //l << "remaining bytes to scan:" << color::lime << n << color::r << l;
        }while(byte != fd.buffer.end());
        log << color::deepskyblue7 << "not a key stroke sequence." << log;
        return {rem::code::rejected,{}};
    }
    kb.kcode = *byte;
    kb.mnemonic = kstroke::CHARACTER;


    return {rem::code::ready,kb};
}

std::string kstroke::name(kstroke::enums en)
{
    std::string str;
    return key_names[en];
}


} //namespace  cat::io
