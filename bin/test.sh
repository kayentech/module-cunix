#!/bin/bash -x

env

if [[ ! -n ${CI} ]]; then
  echo "This scirpt enabled only for continuous integration" && exit 1
fi

if [[ "${TRAVIS_PULL_REQUEST}" == "false" ]]; then
  echo "Continuous integration enabled only for PR's" && exit 0
fi

EX=`echo "${TRAVIS_COMMIT_MESSAGE}" | grep -oE "ex[0-9]{1,2}"`

[[ ! "${EX}" ]] && echo "Invalid commit name" && exit 1

echo "Entering ${PWD}/${EX} directory..."

cd ${PWD}/${EX}

echo "Running tests..."

make test

# exit $?
