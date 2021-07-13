FROM nginx:alpine

COPY content /var/www/
COPY configs/nginx_simple.conf etc/nginx/conf.d/default.conf

RUN apk update
RUN apk add busybox-extras vim

CMD ["nginx", "-g", "daemon off;"]