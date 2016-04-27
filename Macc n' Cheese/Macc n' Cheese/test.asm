LDA       R15,VARS
LD    R7,L1T0
IA    R7,L1T1
STO   R7,L1T1
LD    R7,L1T1
IA    R7,L1T2
STO   R7,L1T2
WRI       L1T2
WRNL      
LD        R0,L2T0
STO       R0,L1T2
LD        R0,L3T0
STO       R0,L2T0
LD    R7,L2T0
IA    R7,L3T0
STO   R7,L3T0
LD        R0,L2T0
STO       R0,L3T0
LD    R7,L3T0
IA    R7,L2T0
STO   R7,L2T0
HALT      
% Data Area ------------
% ----------------------
LABEL    LBL1
INT   0
LABEL    L1T0
INT       1
LABEL    L1T1
INT       3
LABEL    L1T2
INT       4
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
