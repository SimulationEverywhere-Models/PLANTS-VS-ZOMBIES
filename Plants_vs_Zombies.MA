[top]
components : bulletGenerator@BulletGenerator singleZombie yard@Yard
out : succ

Link : bulletOut@bulletGenerator bulletOut@singleZombie
Link : encounter@yard enct@singleZombie
Link : eaten@yard ate@singleZombie

Link : dead@singleZombie death@yard
Link : bit@singleZombie bites@yard
Link : fwd@singleZombie forward@yard

Link : success@yard succ

[singleZombie]
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