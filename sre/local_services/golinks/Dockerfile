FROM golang:alpine

EXPOSE 8067

RUN go install github.com/kellegous/go/cmd/go@latest

CMD ./bin/go --data /var/data
