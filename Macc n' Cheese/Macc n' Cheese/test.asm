LDA       R15,VARS
LD        R0,L1T0
STO       R0,L1T1
LD        R0,L1T1
STO       R0,L1T2
LD        R0,L1T2
STO       R0,L1T3
LD    R7,L1T2
IA    R7,L1T3
STO   R7,L1T3
LD        R0,L2T0
STO       R0,L1T4
LD    R7,L1T3
IM    R7,L1T4
STO   R7,L1T4
LD    R7,L1T1
IS    R7,L1T4
STO   R7,L1T4
WRI       L1T4
WRNL      
LD        R0,L1T4
STO       R0,L1T5
LD    R7,L1T5
IM    R7,L1T6
STO   R7,L1T6
WRI       L1T6
WRNL      
WRI       L1T6
WRI       L2T0
WRI       L3T0
WRNL      
HALT      
% Data Area ------------
% ----------------------
LABEL    LBL1
INT   0
LABEL    L1T0
INT       6
LABEL    L1T1
INT       
LABEL    L1T2
INT       
LABEL    L1T3
INT       
LABEL    L1T4
INT       
LABEL    L1T5
INT       
LABEL    L1T6
INT       2
LABEL    LBL2
INT   0
LABEL    L2T0
INT       3
LABEL    LBL3
INT   0
LABEL    L3T0
INT       5

LABEL     VARS
SKIP      2
