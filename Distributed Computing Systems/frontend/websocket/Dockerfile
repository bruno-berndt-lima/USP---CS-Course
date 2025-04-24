FROM node:20-alpine

WORKDIR /app

ENV TOPIC=updates
# ENV KAFKA_BOOTSTRAP_SERVER=host.docker.internal:9092
ENV KAFKA_BOOTSTRAP_SERVER=kafka:9092

COPY package.json .

RUN npm install

COPY . .

EXPOSE 8082

CMD ["npm", "start"]