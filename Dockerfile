FROM ubuntu:24.04

LABEL "com.talkspirit.maintainer"="Olivier RICARD <olivier+docker@talkspirit.com>"

# Let the conatiner know that there is no tty
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y && apt-get install -y build-essential debhelper devscripts cron software-properties-common wget zsh curl vim zsh git supervisor jq libjq-dev -y

# MongoDB shell tools
RUN wget -qO - https://www.mongodb.org/static/pgp/server-6.0.asc | apt-key add -
RUN echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/ubuntu focal/mongodb-org/6.0 multiverse" | tee /etc/apt/sources.list.d/mongodb-org-6.0.list
RUN LC_ALL=C.UTF-8 add-apt-repository ppa:ondrej/php -y -u && apt-get update

# geoip https://github.com/maxmind/GeoIP2-php

RUN apt-get update && apt-get install -y mongodb-mongosh mongodb-org-tools php8.4-dev php8.4-fpm php8.4-mongodb php8.4-gd php8.4-curl php8.4-cli php8.4-soap php8.4-apcu php8.4-opcache php8.4-intl php8.4-mbstring php8.4-redis php8.4-dom php8.4-zip php8.4-imagick php8.4-bcmath php8.4-mysql && \
echo "date.timezone=${PHP_TIMEZONE:-Europe/Paris}" > /etc/php/8.4/cli/conf.d/date_timezone.ini && \
echo "date.timezone=${PHP_TIMEZONE:-Europe/Paris}" > /etc/php/8.4/fpm/conf.d/date_timezone.ini

RUN wget http://pear.php.net/go-pear.phar && php go-pear.phar

# tools
RUN curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer  && \
    curl -sS http://gordalina.github.io/cachetool/downloads/cachetool.phar -o /usr/local/bin/cachetool.phar && \
    wget https://get.symfony.com/cli/installer -O - | bash && \
    mv /root/.symfony5/bin/symfony /usr/local/bin/symfony  && \
    curl -fLSs https://circle.ci/cli | bash
    
RUN sed -i -e "s/upload_max_filesize\s*=\s*2M/upload_max_filesize = 100M/g" /etc/php/8.4/cli/php.ini && \
    sed -i -e "s/post_max_size\s*=\s*8M/post_max_size = 100M/g" /etc/php/8.4/cli/php.ini && \
    sed -i -e "s/;daemonize\s*=\s*yes/daemonize = no/g" /etc/php/8.4/fpm/php-fpm.conf && \
    sed -i -e "s/listen = \/run\/php\/php8.4-fpm.sock/;listen = \/run\/php\/php8.4-fpm.sock\nlisten = 0:9000/g" /etc/php/8.4/fpm/pool.d/www.conf && \
    sed -i -e "s/upload_max_filesize\s*=\s*2M/upload_max_filesize = 100M/g" /etc/php/8.4/cli/php.ini

RUN apt install -y php8.4-phpdbg gdb

COPY . /tmp/install/php-timecop

# Install timecop & jq
RUN cd /tmp/install/php-timecop && \
    phpize && \
    ./configure && \
    make && \
    make install && \
    echo "extension=timecop.so" >> /etc/php/8.4/cli/php.ini