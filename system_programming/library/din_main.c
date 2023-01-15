
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>




void invoke_method(char *lib, char *method, int argument)
{
  void *dl_handle;
  int (*func)(int);
  char *error;

  
  dl_handle = dlopen(lib, RTLD_LAZY);
  if (!dl_handle) {
    printf( "1 %s\n", dlerror() );
    return;
  }

  /* Resolve the symbol (method) from the object */
  func = dlsym(dl_handle, method);
  error = dlerror();
  if (error != NULL) {
    printf( "2 %s\n", error );
    return;
  }

  /* Call the resolved method and print the result */
  (*func)(argument);

  /* Close the object */
  dlclose( dl_handle );

  return;
}


int main()
{
	 invoke_method("libfoo.so", "Foo", 555 );

return 0;
}

