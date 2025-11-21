start:

    eax = 0
    if(x <= 1) return 0;
    if(x <= 3) return 1;
    if(dil % 2 == 0) return 0;
    ecx = 2

loop:


// --- Here something missing ---


    jne     loop

composite:
    return 0;
prime:
    return 1;
