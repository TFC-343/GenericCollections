# GenericDeque
type-generic double-ended queue in c

## basic example

```c
pDeque deck = DequeNew(double);
DequePush(double, deck, 1);
DequePush(double, deck, 2);
DequePushLeft(double, deck, 0);

printf("%f\n", DequePopLeft(double, deck));
printf("%f\n", DequePopLeft(double, deck));

DequeFree(deck);

>> 0.000000
>> 1.000000
```
