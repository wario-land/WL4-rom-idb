// based on https://gist.github.com/hax0kartik/e358ce447a4537bcef534aa8de84817c
#include <idc.idc>

static EntryDump(f, start)
{
    auto ea, str, teststr1, teststr2, teststr3;

    ea = start;

    while( ea < 0x5000000 )
    {
        str = get_name(ea);
        if( str != "" )
        {
            // Skip entry whose name is the generic unk_XXX
            teststr1 = sprintf("unk_%X", ea);
            teststr2 = sprintf("byte_%X", ea);
            teststr3 = sprintf("word_%X", ea);
            if( teststr1 != str && teststr2 != str && teststr3 != str )
            {
                fprintf(f, "%s 0x%X\n", str, ea);
            }
        }

        ea = next_addr(ea);
    }
}

static main() 
{
    auto current = GetInputFile();
    current = AskFile(-1, current, "Where should I write the symbols to?");
    if(current == 0)
    {
        return -1;
    }
    auto f = fopen(current, "wb");
    Message("EntryDump: Start\n");

    EntryDump(f, 0x3000000);
    fclose(f);
    Message("EntryDump: Done\n");
}
