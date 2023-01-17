#ifndef HEADER_DEQUE_
#define HEADER_DEQUE_

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

#define DEQUE_MAX_SIZE 50

typedef struct Partition__{
    int                max_size;
    struct Partition__ *next;
    bool               is_last;
    struct Partition__ *prev;
    bool               is_first;
    int                top;
    int                bottom;
    void               **data;
} Partition__, *pPartition__;

typedef struct Deque__{
    pPartition__ start;
    pPartition__ end;

} Deque__, *pDeque;

typedef void *hDeque;

pPartition__ PartitionNew(int size_of_data, int bottom, int top){
    pPartition__ part = malloc(sizeof(Partition__));
    part->max_size = DEQUE_MAX_SIZE;

    part->is_last = true;
    part->is_first = true;

    part->bottom = bottom;
    part->top = top;

    part->data = malloc(size_of_data * part->max_size);

    return part;
}

hDeque DequeNew__(int size_of_data){
    pPartition__ part = PartitionNew(size_of_data, DEQUE_MAX_SIZE / 2 - 1, DEQUE_MAX_SIZE / 2);

    pDeque deck = malloc(sizeof(Deque__));
    deck->start = part;
    deck->end = part;

    return (void *) deck;
}

#define DequeNew(T) (DequeNew__(sizeof(T)))

void DequeFree(hDeque deck){
    pDeque deck_ = deck;
    pPartition__ current_part = deck_->start;
    while (!current_part->is_last){
        pPartition__ next_part = current_part->next;
        free(current_part->data);
        free(current_part);
        current_part = next_part;
    }
    free(current_part);

    free(deck_);

}

#define DequePush(T, deck, new_data) { \
    pDeque deck_ = deck;               \
    T* d = (T*)(deck_)->end->data;     \
    d[(deck_)->end->top++] = new_data; \
    if ((deck_)->end->top >= (deck_)->end->max_size){ \
        pPartition__ new_part = PartitionNew(sizeof(T), 0, 0); \
        new_part->prev = (deck_)->end; \
        (deck_)->end->is_last = false; \
        (deck_)->end->next = new_part; \
        (deck_)->end = new_part;       \
    };                                 \
}

#define DequePeak(T, deck) ({ \
    pDeque deck_ = deck;      \
    T r;                      \
    int indx = (deck_)->end->top - 1; \
    if (indx <= -1){          \
        /* indx will be -1 if current partition has no data, gets top of last partition */ \
        r = ((T*)(deck_)->end->prev->data)[(deck_)->end->prev->top - 1]; \
    }                         \
    else{                     \
         r = ((T*)(deck_)->end->data)[indx]; \
    }                         \
    r;                        \
})

#define DequePop(T, deck) ({ \
    pDeque deck_ = deck;     \
    T r;                     \
    int indx = (deck_)->end->top - 1; \
    if (indx <= -1){         \
        /* indx will be -1 if current partition has no data, gets top of last partition */ \
        r = ((T*)(deck_)->end->prev->data)[(deck_)->end->prev->top - 1]; \
        (deck_)->end->prev->is_last = true; \
        (deck_)->end = (deck_)->end->prev; \
        free((deck_)->end->next); \
    }                        \
    else{                    \
         r = ((T*)(deck_)->end->data)[--(deck_)->end->top]; \
    }                        \
    r;                       \
})

#define DequePushLeft(T, deck, new_data) { \
    pDeque deck_ = deck;                   \
    T* d = (T*)(deck_)->start->data;       \
    d[(deck_)->start->bottom--] = new_data; \
    if ((deck_)->start->bottom <= -1){     \
        pPartition__ new_part = PartitionNew(sizeof(T), DEQUE_MAX_SIZE - 1, DEQUE_MAX_SIZE - 1); \
        new_part->next = (deck_)->start;   \
        (deck_)->end->is_first = false;    \
        (deck_)->start->prev = new_part;   \
        (deck_)->start = new_part;         \
    };                                     \
}

#define DequePeakLeft(T, deck) ({ \
    pDeque deck_ = deck;          \
    T r;                          \
    int indx = (deck_)->start->bottom + 1; \
    if (indx >= DEQUE_MAX_SIZE){  \
        r = ((T*)(deck_)->start->next->data)[(deck_)->start->next->bottom + 1]; \
    }                             \
    else{                         \
         r = ((T*)(deck_)->start->data)[indx]; \
    }                             \
    r;                            \
})

#define DequePopLeft(T, deck) ({ \
    pDeque deck_ = deck;         \
    T r;                         \
    int indx = (deck_)->start->bottom + 1; \
    if (indx >= DEQUE_MAX_SIZE){ \
        r = ((T*)(deck_)->start->next->data)[(deck_)->start->next->bottom + 1]; \
        (deck_)->start->next->is_first = true; \
        (deck_)->start = (deck_)->start->next; \
        free((deck_)->start->prev); \
    }                            \
    else{                        \
         r = ((T*)(deck_)->start->data)[++(deck_)->start->bottom]; \
    }                            \
    r;                           \
})

#endif
