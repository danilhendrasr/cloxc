#include "chunk.h"
#include "debug.h"

int main(int argc, char const* argv[])
{
  Chunk chunk;

  initChunk(&chunk);
  writeChunk(&chunk, OP_RETURN);

  disassembleChunk(&chunk, "Testing chunk");

  freeChunk(&chunk);

  return 0;
}
