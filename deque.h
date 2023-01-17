#ifndef HEADER_DEQUE_
#define HEADER_DEQUE_

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

#define DEQUE_MAX_SIZE 50

typedef struct internal_Partition{
    int max_size;

    struct internal_Partition* next;
    bool is_last;
    struct internal_Partition* prev;
    bool is_first;

    int top;
    int bottom;

    void** data;
} internal_Partition;

typedef struct Deque{
    internal_Partition* start;
    internal_Partition* end;

} Deque;

typedef Deque* pDeque;

internal_Partition* PartitionNew(int size_of_data, int bottom, int top){
    internal_Partition* part = malloc(sizeof(internal_Partition));
    part->max_size = DEQUE_MAX_SIZE;

    part->is_last = true;
    part->is_first = true;

    part->bottom = bottom;
    part->top = top;

    part->data = malloc(size_of_data * part->max_size);

    return part;
}

pDeque internal_DequeNew(int size_of_data){
    internal_Partition* part = PartitionNew(size_of_data, DEQUE_MAX_SIZE / 2 - 1, DEQUE_MAX_SIZE / 2);

    pDeque deck = malloc(sizeof(Deque));
    deck->start = part;
    deck->end = part;

    return deck;
}

#define DequeNew(T) (internal_DequeNew(sizeof(T)))

void DequeFree(pDeque deck){
    internal_Partition* current_part = deck->start;
    while (!current_part->is_last){
        internal_Partition* next_part = current_part->next;
        free(current_part->data);
        free(current_part);
        current_part = next_part;
    }
    free(current_part);

    free(deck);

}

#define DequePush(T, deck, new_data) { \
    T* d = (T*)(deck)->end->data;      \
    d[(deck)->end->top++] = new_data;  \
    if ((deck)->end->top >= (deck)->end->max_size){ \
        internal_Partition* new_part = PartitionNew(sizeof(T), 0, 0); \
        new_part->prev = (deck)->end;  \
        (deck)->end->is_last = false;  \
        (deck)->end->next = new_part;  \
        (deck)->end = new_part;        \
    };                                 \
}

#define DequePeak(T, deck) ({ \
    T r;                      \
    int indx = (deck)->end->top - 1; \
    if (indx <= -1){          \
        /* indx will be -1 if current partition has no data, gets top of last partition */ \
        r = ((T*)(deck)->end->prev->data)[(deck)->end->prev->top - 1]; \
    }                         \
    else{                     \
         r = ((T*)(deck)->end->data)[indx]; \
    }                         \
    r;                        \
})

#define DequePop(T, deck) ({ \
    T r;                     \
    int indx = (deck)->end->top - 1; \
    if (indx <= -1){         \
        /* indx will be -1 if current partition has no data, gets top of last partition */ \
        r = ((T*)(deck)->end->prev->data)[(deck)->end->prev->top - 1]; \
        (deck)->end->prev->is_last = true; \
        (deck)->end = (deck)->end->prev; \
        free((deck)->end->next); \
    }                        \
    else{                    \
         r = ((T*)(deck)->end->data)[--(deck)->end->top]; \
    }                        \
    r;                       \
})

#define DequePushLeft(T, deck, new_data) { \
    T* d = (T*)(deck)->start->data;        \
    d[(deck)->start->bottom--] = new_data; \
    if ((deck)->start->bottom <= -1){      \
        internal_Partition* new_part = PartitionNew(sizeof(T), DEQUE_MAX_SIZE - 1, DEQUE_MAX_SIZE - 1); \
        new_part->next = (deck)->start;    \
        (deck)->end->is_first = false;     \
        (deck)->start->prev = new_part;    \
        (deck)->start = new_part;          \
    };                                     \
}

#define DequePeakLeft(T, deck) ({ \
    T r;                          \
    int indx = (deck)->start->bottom + 1; \
    if (indx >= DEQUE_MAX_SIZE){  \
        /* indx will be -1 if current partition has no data, gets top of last partition */ \
        r = ((T*)(deck)->start->next->data)[(deck)->start->next->bottom + 1]; \
    }                             \
    else{                         \
         r = ((T*)(deck)->start->data)[indx]; \
    }                             \
    r;                            \
})

#define DequePopLeft(T, deck) ({ \
    T r;                         \
    int indx = (deck)->start->bottom + 1; \
    if (indx >= DEQUE_MAX_SIZE){ \
        r = ((T*)(deck)->start->next->data)[(deck)->start->next->bottom + 1]; \
        (deck)->start->next->is_first = true; \
        (deck)->start = (deck)->start->next; \
        free((deck)->start->prev); \
    }                            \
    else{                        \
         r = ((T*)(deck)->start->data)[++(deck)->start->bottom]; \
    }                            \
    r;                           \
})

#endif
