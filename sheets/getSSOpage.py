#!/usr/bin/env python3
#
# A simple script to get a page from behind the "new" SSO at CERN (OAuth2)
# using the auth-get-sso-cookie package 
#
# Author: andreas.pfeiffer@cern.ch
#
import logging
import requests
#
# 
# For the following, I simply checked out the repo in my ~/python/ dir and then set a symlink:
# mkdir ~/python && cd $_
# git clone https://:@gitlab.cern.ch:8443/authzsvc/docs/auth-get-sso-cookie.git
# cd -
# ln -s ~/python/auth-get-sso-cookie/auth_get_sso_cookie/cern_sso.py .
# 
from cern_sso import login_with_kerberos
#
logging.basicConfig(format = '%(message)s', level=logging.INFO)
#
messages = {}
#
def getAuthCookies(url):
    try:
       verify_cert=True # '/etc/grid-security/certificates/CERN-GridCA.pem'
       auth_hostname='auth.cern.ch'
       session, response = login_with_kerberos(url, verify_cert, auth_hostname, silent=False)
       if response.status_code == 302:
           redirect_uri = response.headers["Location"]
           logging.info( "Logged in. Fetching redirect URL to get application cookies")
           session.get(redirect_uri, verify=verify_cert)
       logging.debug(  "Returning cookies")
       return session.cookies
    except Exception as e:
        logging.error( "An error occurred while trying to log in and get cookies for %s, %s" % (url, str(e)) )
    #
    return None
#
def check(url):
    authCookies = getAuthCookies( url )
    if not authCookies:
        logging.error( 'Could not login to %s to get cookies -- aborting.' % url )
        return
    #
    res = requests.get( url, allow_redirects=True, cookies=authCookies )
    #
    expectedHttpCode = 200
    expectedRes = 'CERN Computing Blog'
    #
    if res.status_code != expectedHttpCode:
        logging.error( 'checkURLs> Error: Illegal status %d found for %s ' % (res.status_code, url)  )
    else:
        if expectedRes.strip() not in res.text:
            logging.error( 'string "%s" NOT found in page:' % expectedRes )
        else:
            logging.info( 'string "%s" found in page.' % expectedRes )
#
url = 'https://computing-blog.web.cern.ch'
check( url )