#ifndef _STDLIB_H 
#include <stdlib.h>
#endif

typedef struct arena {
	void * memory;
	int current_size;
	int maximum_size;  
} arena;

int arena_max_size(arena * arena_pointer);
int arena_current_size(arena * arena_pointer);
void arena_free(arena * arena_pointer);
void * arena_alloc(arena * arena_pointer, int requested_size);
arena * new_arena(int arena_size);

arena * new_arena(int arena_size) {
	arena * new_arena = (arena *)calloc(1, sizeof(arena));
	new_arena ->memory = calloc(arena_size, sizeof(char)); 	
	new_arena ->maximum_size = arena_size;
	new_arena ->current_size = 0;
	return new_arena; 
}

void * arena_alloc(arena * arena_pointer, int requested_size){
	int new_size =arena_pointer ->current_size + requested_size;
	if ( new_size >= arena_pointer -> maximum_size) {
		arena_pointer->memory = realloc(arena_pointer->memory, sizeof(char)*new_size*2); 
		arena_pointer->maximum_size = new_size * 2;
	}
	void * return_pointer = (void *) ((char *)arena_pointer->memory + arena_pointer->current_size);
	arena_pointer->current_size += requested_size;
	return return_pointer;
}

void arena_free(arena * arena_pointer){
	free(arena_pointer->memory);
	free(arena_pointer);
}

int arena_current_size(arena * arena_pointer){
	return arena_pointer->current_size;
}

int arena_max_size(arena * arena_pointer){
	return arena_pointer->maximum_size;
}

#ifdef TESTMODE
int main(){
	//tests
	arena * my_arena = new_arena(sizeof(int)*8);
	int * one_to_three = (int *)arena_alloc(my_arena,sizeof(int)*3);	
	one_to_three[0] = 0;
	one_to_three[1] = 1;
	one_to_three[2] = 2;
	int * four_to_six= (int *)arena_alloc(my_arena,sizeof(int)*3);	
	four_to_six[0] = 3;
	four_to_six[1] = 4;
	four_to_six[2] = 5;
	int * seven_to_ten= (int *)arena_alloc(my_arena,sizeof(int)*3);	
	seven_to_ten[0] = 6;
	seven_to_ten[1] = 7;
	seven_to_ten[2] = 8;

	#include <assert.h>
	assert(one_to_three[0] == 0);
	assert(one_to_three[1] == 1);
	assert(one_to_three[2] == 2);
	assert(four_to_six[0] == 3);
	assert(four_to_six[1] == 4);
	assert(four_to_six[2] == 5);
	assert(seven_to_ten[0] == 6);
	assert(seven_to_ten[1] == 7);
	assert(seven_to_ten[2] == 8);
	assert(arena_current_size(my_arena) == 9*sizeof(int));
		
	arena_free(my_arena);
}  
#endif











