[top]
components :  health@Health speed@Speed bite@Bite
in : bulletOut
in : enct
in : ate
out : dead
out : bit
out : fwd

Link : bulletOut hit@health
Link : enct encounter@bite
Link : enct encounter@speed
Link : ate eaten@bite
Link : ate eaten@speed

Link : death@health death@speed

Link : death@health dead
Link : bites@bite  bit
Link : forward@speed fwd