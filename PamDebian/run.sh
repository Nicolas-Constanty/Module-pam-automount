echo -n "Stop " && sudo docker stop pam_test
echo -n "Remove " && sudo docker rm pam_test
echo "Start pam_test"
sudo docker run -i -t -v $PWD/pam_modules/:/media/pam_modules --name pam_test pam_debian /bin/bash
