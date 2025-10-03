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

#include <catui/io/kstroke.h>

namespace cat::io
{

kstroke kstroke::none{kstroke::NO_KEY, 0, "no key"};



kstroke::kstroke(kstroke::enums e, u64 c, std::string n): mnemonic(e), kcode(c), name(n){}





kstroke::dbgroup kstroke::keysdb
{
    {kstroke::ARROW_UP              ,0x00000000001b5b41,"arrowup"               },
    {kstroke::ARROW_DOWN            ,0x00000000001b5b42,"arrowdown"             },
    {kstroke::ARROW_LEFT            ,0x00000000001b5b44,"arrowleft"             },
    {kstroke::ARROW_RIGHT           ,0x00000000001b5b43,"arrowright"            },
    {kstroke::ENTER                 ,0x000000000000000a,"enter"                 },
    {kstroke::ESCAPE                ,0x000000000000001b,"escape/cancel/dismiss" },
    {kstroke::BACKSPACE             ,0x000000000000007f,"backspace"             },
    {kstroke::HOME                  ,0x00000000001b5b48,"home"                  },
    {kstroke::END                   ,0x00000000001b5b46,"end"                   },
    {kstroke::PAGE_UP               ,0x000000001b5b357e,"pageup"                },
    {kstroke::PAGE_DOWN             ,0x000000001b5b367e,"pagedown"              },
    {kstroke::INSERT                ,0x000000001b5b327e,"insert"                },
    {kstroke::DELETE                ,0x000000001b5b337e,"delete"                },
    {kstroke::TAB                   ,0x0000000000000009,"tab"                   },
    {kstroke::F1                    ,0x00000000001b4f50,"f1"                    },
    {kstroke::F2                    ,0x00000000001b4f51,"f2"                    },
    {kstroke::F3                    ,0x00000000001b4f52,"f3"                    },
    {kstroke::F4                    ,0x00000000001b4f53,"f4"                    },
    {kstroke::F5                    ,0x0000001b5b31357e,"f5"                    },
    {kstroke::F6                    ,0x0000001b5b31377e,"f6"                    },
    {kstroke::F7                    ,0x0000001b5b31387e,"f7"                    },
    {kstroke::F8                    ,0x0000001b5b31397e,"f8"                    },
    {kstroke::F9                    ,0x0000001b5b32307e,"f9"                    },
    {kstroke::F10                   ,0x0000001b5b32317e,"f10"                   },
    {kstroke::F11                   ,0x0000001b5b32337e,"f11"                   },
    {kstroke::F12                   ,0x0000001b5b32347e,"f12"                   },
    {kstroke::SHIFT_ARROW_UP        ,0x00001b5b313b3241,"shift+arrowup"         },
    {kstroke::SHIFT_ARROW_DOWN      ,0x00001b5b313b3242,"shift+arrowdown"       },
    {kstroke::SHIFT_ARROW_LEFT      ,0x00001b5b313b3244,"shift+arrowleft"       },
    {kstroke::SHIFT_ARROW_RIGHT     ,0x00001b5b313b3243,"shift+arrowright"      },
    {kstroke::SHIFT_END             ,0x00001b5b313b3246,"shift+end"             },
    {kstroke::SHIFT_HOME            ,0x00001b5b313b3248,"shift+home"            },
    {kstroke::SHIFT_PAGE_UP         ,0x00001b5b353b327e,"shift+pageup"          },
    {kstroke::SHIFT_PAGE_DOWN       ,0x00001b5b363b327e,"shift+pagedown"        },
    {kstroke::SHIFT_F1              ,0x000000001b4f3250,"shift+f1"              },
    {kstroke::SHIFT_F2              ,0x000000001b4f3251,"shift+f2"              },
    {kstroke::SHIFT_F3              ,0x000000001b4f3252,"shift+f3"              },
    {kstroke::SHIFT_F4              ,0x000000001b4f3253,"shift+f4"              },
    {kstroke::SHIFT_F5              ,0x001b5b31353b327e,"shift+f5"              },
    {kstroke::SHIFT_F6              ,0x001b5b31373b327e,"shift+f6"              },
    {kstroke::SHIFT_F7              ,0x001b5b31383b327e,"shift+f7"              },
    {kstroke::SHIFT_F8              ,0x001b5b31393b327e,"shift+f8"              },
    {kstroke::SHIFT_F9              ,0x001b5b32303b327e,"shift+f9"              },
    {kstroke::SHIFT_F10             ,0x001b5b32313b327e,"shift+f10"             },
    {kstroke::SHIFT_F11             ,0x001b5b32333b327e,"shift+f11"             },
    {kstroke::SHIFT_F12             ,0x001b5b32343b327e,"shift+f12"             },
    {kstroke::SHIFT_TAB             ,0x00000000001b5b5a,"shift+tab"             },
    {kstroke::SHIFT_ENTER           ,0x00000000001b4f4d,"shift+enter"           },
    {kstroke::CTRL_PAGE_UP          ,0x00001b5b353b357e,"ctrl+pageup"           },
    {kstroke::CTRL_PAGE_DOWN        ,0x00001b5b363b357e,"ctrl+pagedown"         },
    {kstroke::CTRL_DELETE           ,0x00001b5b333b357e,"ctrl+delete"           },
    {kstroke::CTRL_END              ,0x00001b5b313b3546,"ctrl+end"              },
    {kstroke::CTRL_ARROW_LEFT       ,0x00001b5b313b3544,"ctrl+arrowleft"        },
    {kstroke::CTRL_ARROW_RIGHT      ,0x00001b5b313b3543,"ctrl+arrowright"       },
    {kstroke::CTRL_ARROW_UP         ,0x00001b5b313b3541,"ctrl+arrowup"          },
    {kstroke::CTRL_ARROW_DOWN       ,0x00001b5b313b3542,"ctrl+arrowdown"        },
    {kstroke::CTRL_HOME             ,0x00001b5b313b3548,"ctrl+home"             },
    {kstroke::CTRL_INSERT           ,0x00001b5b323b357e,"ctrl+insert"           },
    {kstroke::CTRL_Q                ,0x0000000000000011,"ctrl+q"                },
    {kstroke::CTRL_S                ,0x0000000000000013,"ctrl+s"                },
    {kstroke::CTRL_V                ,0x0000000000000016,"ctrl+v"                },
    {kstroke::CTRL_BACKSPACE        ,0x0000000000000008,"ctrl+back-space"       },
    {kstroke::CTRL_F8               ,0x001b5b31393b357e,"ctrl+f8"               },
    {kstroke::ALT_ARROW_LEFT        ,0x00001b5b313b3344,"alt+arrowleft"         },
    {kstroke::ALT_ARROW_RIGHT       ,0x00001b5b313b3343,"alt+arrowright"        },
    {kstroke::ALT_ARROW_UP          ,0x00001b5b313b3341,"alt+arrowup"           },
    {kstroke::ALT_ARROW_DOWN        ,0x00001b5b313b3342,"alt+arrowdown"         },
    {kstroke::SHIFT_CTRL_ARROW_LEFT ,0x00001b5b313b3644,"shift+ctrl+arrowleft"  },
    {kstroke::SHIFT_CTRL_ARROW_RIGHT,0x00001b5b313b3643,"shift+ctrl+arrowright" },
    {kstroke::SHIFT_CTRL_ARROW_UP   ,0x00001b5b313b3641,"shift+ctrl+arrowup"    },
    {kstroke::SHIFT_CTRL_ARROW_DOWN ,0x00001b5b313b3642,"shift+ctrl+arrowdown"  },
    {kstroke::SHIFT_CTRL_DEL        ,0x00001b5b313b3646,"shift+ctrl+del"        },
    {kstroke::SHIFT_CTRL_HOME       ,0x00001b5b313b3648,"shift+ctrl+home"       },
    {kstroke::SHIFT_ALT_ARROW_LEFT  ,0x00001b5b313b3444,"shift+alt+arrowleft"   },
    {kstroke::SHIFT_ALT_ARROW_RIGHT ,0x00001b5b313b3443,"shift+alt+arrowright"  },
    {kstroke::SHIFT_ALT_ARROW_UP    ,0x00001b5b313b3441,"shift+alt+arrowup"     },
    {kstroke::SHIFT_ALT_ARROW_DOWN  ,0x00001b5b313b3442,"shift+alt+arrowdown"   },
    {kstroke::SHIFT_ALT_END         ,0x00001b5b313b3446,"shift+alt+end"         },
    {kstroke::SHIFT_ALT_HOME        ,0x00001b5b313b3448,"shift+alt+home"        },
    {kstroke::SHIFT_ALT_PAGE_UP     ,0x00001b5b353b347e,"shift+alt+pageup"      },
    {kstroke::SHIFT_ALT_PAGE_DOWN   ,0x00001b5b363b347e,"shift+alt+pagedown"    },
    {kstroke::CTRL_ALT_ARROW_LEFT   ,0x00001b5b313b3744,"ctrl+alt+arrowleft"    },
    {kstroke::CTRL_ALT_ARROW_RIGHT  ,0x00001b5b313b3743,"ctrl+alt+arrowright"   },
    {kstroke::CTRL_ALT_ARROW_UP     ,0x00001b5b313b3741,"ctrl+alt+arrowup"      },
    {kstroke::CTRL_ALT_ARROW_DOWN   ,0x00001b5b313b3742,"ctrl+alt+arrowdown"    },
    {kstroke::CHARACTER             ,0x0000000000000000,"char input"            }, ///< never hit.


    //...
};





kstroke kstroke::query(u64 code_seq)
{
    for (auto const &k : kstroke::keysdb)
        if (k.kcode == code_seq) return k;
    return none;
}


kstroke kstroke::query(std::string_view s)
{
    for (auto const&k : kstroke::keysdb)
        if (k.name == s)
            return k;
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
    auto str = utxt::bytes(fd.buffer);
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
    kb.name = "char input";

    return {rem::code::ready,kb};
}

} //namespace  cat::io
