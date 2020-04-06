
#( sleep 4 && docker exec jekyll ruby -run -ehttpd /srv/jekyll/_site -p4000 >/dev/null 2>&1 ) &
docker run --name jekyll \
	--rm --volume="$PWD:/srv/jekyll" \
	-p 8092:4000 \
	-it jekyll/jekyll \
	jekyll serve --force_polling --drafts --incremental

