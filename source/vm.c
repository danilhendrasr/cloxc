#include "vm.h"

#include <stdint.h>
#include <stdio.h>

#include "chunk.h"
#include "debug.h"
#include "value.h"

VM vm;

static void resetStack(void)
{
  vm.stackTop = vm.stack;
}

void initVM(void)
{
  resetStack();
}

void freeVM(void) {}

void push(Value value)
{
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop(void)
{
  vm.stackTop--;
  return *vm.stackTop;
}

static InterpretResult run(void)
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("    ");
    for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");

    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
      case OP_CONSTANT: {
        Value constant = READ_CONSTANT();
        push(constant);
        printValue(constant);
        printf("\n");
        break;
      }

      case OP_NEGATE:
        push(-pop());
        break;

      case OP_RETURN: {
        printValue(pop());
        printf("\n");
        return INTERPRET_OK;
      }
    }
  }

#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult interpret(Chunk* chunk)
{
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}
