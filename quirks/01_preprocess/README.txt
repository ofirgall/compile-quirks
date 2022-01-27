#######################

Every #keyword is a command for the preproccesor.

#include, #define, #if, #endif, #else, #error, comments and more.

To examine how to preproccesor works use the `-E` flag.
`gcc main.c -E | less`

If we go to the end of the output we will see that the preproccesor replaced MY_NUM with (50).
In addition he replaced #include <stdio.h> with stdio.h content.

#######################

We can see that there are lines like this `# 2 "main.c" 2` those lines are use to traceback errors.

In this error:
"""
chatmaster.cpp:220: error: no matching function for call to ‘ChatMaster::connect(const ContactList*&, const char [35], ChatMaster* const, const char [39])’
/usr/lib/qt3/include/qobject.h:116: note: candidates are: static bool QObject::connect(const QObject*, const char*, const QObject*, const char*)
/usr/lib/qt3/include/qobject.h:226: note: bool QObject::connect(const QObject*, const char*, const char*) const
"""

chatmaster.cpp:220 was a hint
/usr/lib/qt3/include/qobject.h:116 was a hint
/usr/lib/qt3/include/qobject.h:226 was a hint

#######################

Some flags that passed to the preproccesor:
-D: defines, like #define
	* -DMY_NUM_OVERRIDE: equivalent to #define MY_NUM_OVERRIDE
	* -DMY_NUM=100: equivalent to #define MY_NUM 100
-include: includes file, like #include
	* -include "<stdio.h>": equivalent to #include <stdio.h>

I recommend to try to compile `main.c` with each example here and add `-E` flag to see the results
