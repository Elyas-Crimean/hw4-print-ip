#!/bin/sh
set -x

GH_REPO_REF=github.com/Elyas-Crimean/hw4-print-ip
GH_REPO_NAME=hw4-print-ip

mkdir docs
cd docs
git clone -b gh-pages https://git@$GH_REPO_REF
cd $GH_REPO_NAME

git config --global push.default simple
git config user.name "Travis CI"
git config user.email "travis@travis-ci.org"

rm -rf *
echo "" > .nojekyll

doxygen $TRAVIS_BUILD_DIR/Doxyfile 2>&1 | tee doxygen.log

if [ -d "html" ] && [ -f "html/index.html" ]; then

    echo 'Uploading documentation to the gh-pages branch...'
    mv html/* ./
    rmdir html

    git add --all

    git commit -m "Deploy code docs to GitHub Pages Travis build: ${TRAVIS_BUILD_NUMBER}" -m "Commit: ${TRAVIS_COMMIT}"

    git push --force "https://${GH_REPO_TOKEN}@${GH_REPO_REF}" > /dev/null 2>&1

else
    echo '' >&2
    echo 'Warning: No documentation (html) files have been found!' >&2
    echo 'Warning: Not going to push the documentation to GitHub!' >&2
    exit 1
fi
