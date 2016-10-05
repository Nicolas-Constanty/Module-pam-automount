command -v docker >/dev/null 2>&1
if [ $? = 1 ] || [ ! -z "$1" ]; then
	if [ $1 = "fedora" ]; then
		sudo dnf update
		sudo tee /etc/yum.repos.d/docker.repo <<-'EOF'
		[dockerrepo]
		name=Docker Repository
		baseurl=https://yum.dockerproject.org/repo/main/fedora/$releasever/
		enabled=1
		gpgcheck=1
		gpgkey=https://yum.dockerproject.org/gpg
		EOF
		sudo dnf install docker-engine
		sudo systemctl enable docker.service
		sudo systemctl start docker
	elif [ $1 = "ubuntu" ]; then
		sudo apt-get update
		sudo apt-get install apt-transport-https ca-certificates
		sudo apt-get install linux-image-extra-$(uname -r) linux-image-extra-virtual
		echo 'deb https://apt.dockerproject.org/repo ubuntu-xenial main' | sudo tee --append /etc/apt/sources.list.d/docker.list
		sudo apt-get update
		sudo apt-get purge lxc-docker
		apt-cache policy docker-engine
		sudo apt-get update
 		sudo apt-get install docker-engine
		sudo service docker start
	else
		echo -e "\033[0;32mFor full installing(docker + image_pam) do :\033[0m"
		echo -e "\033[0;33mFedora :\n./install.sh -fedora"
		echo -e "Ubuntu :\n./install.sh -ubuntu\033[0m"
		exit
	fi
fi
sudo docker build -t pam_debian:latest .
./run.sh
