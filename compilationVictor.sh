gcc -fPIC -DPIC -shared -rdynamic -o ../../shareVM/test_coucou.so test_coucou.c
ssh victorgouet@127.0.0.1 -p 2222 -t "ls ; ./copyLIB.sh"

# fichier pour configurer/ ajouter un module pam
# /etc/pam.d/common-session

# on cp la lib 
# cp /media/sf_shareVM/test_coucou.so /lib/x86_64-linux-gnu/security/
