.PHONY: build clean deploy

# Commands
DOCKER		?= docker
GREP		?= grep
SERVERLESS	?= serverless

# Automake-like silent rules
V ?= 0
AT_DOCKER         = $(AT_DOCKER_$(V))
AT_DOCKER_0       = @echo "  DOCKER       "$@;
AT_DOCKER_1       =
AT_RUN			  = $(AT_RUN_$(V))
AT_RUN_0		  = @echo "  RUN          "$@;
AT_RUN_1		  =

# =====
# build
# =====
build:
	env GOOS=linux go build -ldflags="-s -w" -o bin/world go/world/main.go

clean:
	rm -rf ./bin

deploy: clean build
	$(AT_RUN) $(SERVERLESS) deploy --verbose --stage local

# ========
# services
# ========

setup-serverless:
	$(AT_RUN) $(SERVERLESS) plugin install -n serverless-localstack

setup-localstack:
	$(AT_DOCKER)if ! $(DOCKER) ps | $(GREP) aws.$(USER); then \
		$(DOCKER) run --name aws.$(USER) \
			-p 4566:4566 \
			-p 8080:8080 \
			-v /var/run/docker.sock:/var/run/docker.sock \
			-e TMP=/tmp \
			-e HOST_TMP_FOLDER=/tmp/localstak \
			-e DATA_DIR=/tmp/localstack/data \
			-e LAMBDA_EXECUTOR=docker-reuse \
			--restart always \
			-d localstack/localstack-full && \
		echo 'Waiting 1 sec for aws to initialize ...'; \
		sleep 1; \
	fi

remove-localstack:
	$(AT_DOCKER) $(DOCKER) rm -v -f aws.$(USER)
