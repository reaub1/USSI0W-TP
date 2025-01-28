
# TP4 - Docker

TO DO 

---

## 1 - Proposer un service 

récupération de Jenkins via docker hub :
```bash
docker pull jenkins/jenkins:lts
```

Exposer le service : 

```bash 
docker run -d -p 8080:8080 --name jenkins jenkins/jenkins:lts
```

on se connecte à l'url : http://localhost:8080

on cherche le mot de passe pour unlock jenkins :

pour retrouver le container id
```bash
docker ps -a 
```

pour se connecter au serveur : 
```bash
docker exec -it  <container id> /bin/bash
```

pour afficher le mot de passe : 

```bash
cat /var/jenkins_home/secrets/initialAdminPassword
```

Arrêter le docker : 

```bash
docker stop jenkins
```

## 2 - Service from scratch 

récuperer l'image docket tomcat : 
```bash
docker pull tomcat:latest
```

Voir configuration du docker file : .\dockerfile

construction de l'image :
```bash
docker build -t jenkins-tomcat .
```

On run le docker : 
```bash
docker run -d -p 8080:8080 --name jenkins-tomcat jenkins-tomcat
```

on teste le service : 
```bash
http://localhost:8080/jenkins
```

On cherche le mot de passe comme dans le dernier exercice.

pour arrêter le service : 
```bash
docker stop jenkins-tomcat
```