
void dummy_test_entrypoint()
{

}

void main()
{
    char* video_mem = (char*) 0xb8000;      // Stores 0xb8000 (video memory address) into video_mem pointer
    *video_mem = 'X';
}