Load TopLeft
          Store LFStart
          Load SquareWidth
          Store LFLen
          Load ONE
          Store LFInc
          Load RED
          Store LFColor
          JnS LineFun


          Load BottomLeft
          Store LFStart
          Load SquareWidth
          Store LFLen
          Load ONE
          Store LFInc
          Load RED
          Store LFColor
          JnS LineFun


          Load TopLeft
          Store LFStart
          Load SquareHeight
          Store LFLen
          Load TENH
          Store LFInc
          Load RED
          Store LFColor
          JnS LineFun


          Load TopRight
          Store LFStart
          Load SquareHeight
          Store LFLen
          Load TENH
          Store LFInc
          Load RED
          Store LFColor
          JnS LineFun


          Load InnerStart
          Store LFStart
          Load InnerHeight
          Store FillRows
FillLoop,  Load LFStart
          Store CurrentRowStart
          Load InnerWidth
          Store LFLen
          Load ONE
          Store LFInc
          Load BLUE
          Store LFColor
          JnS LineFun


          Load CurrentRowStart
          Add TENH
          Store LFStart


          Load FillRows
          Subt ONE
          Store FillRows
          Skipcond 400
          Jump FillLoop


          Load BottomRight
          Store LFStart
          Load DiagonalLen
          Store LFLen
          Load ONE
          Add TENH
          Store LFInc
          Load GREEN
          Store LFColor
          JnS LineFun


          Halt


TopLeft,       HEX 0F00
BottomLeft,    HEX 0F40
TopRight,      HEX 0F04
BottomRight,   HEX 0F44
SquareWidth,   HEX 5
SquareHeight,  HEX 5
InnerStart,    HEX 0F11
InnerWidth,    HEX 3
InnerHeight,   HEX 3
FillRows,      HEX 0
CurrentRowStart, HEX 0
DiagonalLen,   HEX 5
DiagonalInc,   HEX 11
ONE,           HEX 1
TENH,          HEX 10
RED,           HEX 7C00
BLUE,          HEX 001F
GREEN,         HEX 03E0


LineFun,       HEX 0
LFLoop,        Load LFColor
               StoreI LFStart
               Load LFStart
               Add LFInc
               Store LFStart
               Load LFLen
               Subt ONE
               Store LFLen
               Skipcond 400
               Jump LFLoop
               JumpI LineFun


LFStart,       HEX 0
LFLen,         HEX 0
LFInc,         HEX 0
LFColor,       HEX 0