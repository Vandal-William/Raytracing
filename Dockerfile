FROM alpine:3.19

RUN apk add --no-cache \
    build-base \
    cmake \
    bash \
    nodejs \
    npm

ENV RAYTRACING_IN_CONTAINER=1

WORKDIR /app

COPY . .

RUN npm run build:release

CMD ["npm", "start"]
