/*
**  mod_randomtrip.c -- Apache sample randomtrip module
**  [Autogenerated via ``apxs -n randomtrip -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory
**  by running:
**
**    $ apxs -c -i mod_randomtrip.c
**
**  Then activate it in Apache's apache2.conf file for instance
**  for the URL /randomtrip in as follows:
**
**    #   apache2.conf
**    LoadModule randomtrip_module modules/mod_randomtrip.so
**    <Location /randomtrip>
**    SetHandler randomtrip
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /randomtrip and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/randomtrip
**
**  The output should be similar to the following one:
**
**    HTTP/1.1 200 OK
**    Date: Tue, 31 Mar 1998 14:42:22 GMT
**    Server: Apache/1.3.4 (Unix)
**    Connection: close
**    Content-Type: text/html
**
**    The sample page from mod_randomtrip.c
*/

#include <sstream>

#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_protocol.h"
#include "ap_config.h"
#include "util_script.h"

#include "visited.h"
#include "range.h"

using std::ostringstream;
using std::stod;
using std::string;

string get_string(apr_table_t* GET, const char* param, string def) {
  auto* value = apr_table_get(GET, param);
  if (value) {
    def = value;
  }
  return def;
}

int get_int(apr_table_t* GET, const char* param, int def) {
  auto* value = apr_table_get(GET, param);
  if (value) {
    def = std::stoi(value);
  }
  return def;
}

double get_double(apr_table_t* GET, const char* param, double def) {
  auto* value = apr_table_get(GET, param);
  if (value) {
    def = stod(value);
  }
  return def;
}

Visited get_visited(apr_table_t* GET, const char* param, Visited def) {
  auto* value = apr_table_get(GET, param);
  if (value) {
    def = Visited(value);
  }
  return def;
}

void latlon(ostringstream& html, double lat, double lon) {
  html << "(" << lat << ", " << lon << ")";
}

void mapslatlon(ostringstream& html, Point point) {
  html << "new google.maps.LatLng(" << point.String() << ")";
}

template<typename T>
void hidden(ostringstream& html, string name, T value) {
  html << "        <input type=\"hidden\" name=\"" << name << "\" value=\"" << value << "\">\n";
}

void marker(ostringstream& html, Point point) {
  html << "marker = new google.maps.Marker({\n\
        map: map\n\
    });\n\
    marker.setPosition(";
  mapslatlon(html, point);
  html << ");\n";
}

string get_uri(string hostname, string uri) {
  ostringstream link;
  link << "http://" << hostname << uri;
  return link.str();
}

string get_link(string hostname,
                string uri,
                int is_lat,
                Point start,
                Point end,
                Visited visited,
                int zoom,
                string old_picked) {
  ostringstream link;
  link << get_uri(hostname, uri);
  link << "?is_lat=" << is_lat;
  link << "&slat=" << start.lat_;
  link << "&slon=" << start.lon_;
  link << "&elat=" << end.lat_;
  link << "&elon=" << end.lon_;
  link << "&visited=" << visited.String();
  link << "&zoom=" << zoom;
  link << "&old_picked=" << old_picked;
  return link.str();
}

string get_new_picked(int picked, string old_picked) {
  if (picked < 1 || picked > 6) {
    return old_picked;
  }
  ostringstream np;
  if (!old_picked.empty()) {
    np << old_picked << ",";
  }
  np << picked;
  return np.str();
}

const string get_html(string hostname,
                      string uri,
                      int is_lat,
                      int picked,
                      Point start,
                      Point end,
                      Visited visited,
                      int zoom,
                      string old_picked) {
  if (picked >= 1 && picked <= 6) {
    Point new_start, new_end;
    AddPicked(visited, 6, picked, is_lat, start, end, &new_start, &new_end);
    start = new_start;
    end = new_end;
  }
  auto highest = Highest(visited, start, end);
  auto new_picked = get_new_picked(picked, old_picked);
  ostringstream html;
  html << "<!DOCTYPE html>\n\
<html>\n\
  <head>\n\
    <meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\">\n\
    <meta charset=\"utf-8\">\n\
    <title>Wild Journey</title>\n\
    <style>\n\
      html, body, #map-canvas {\n\
        height: 100%;\n\
        margin: 0px;\n\
        padding: 0px\n\
      }\n\
    </style>\n\
    <script src=\"http://ajax.googleapis.com/ajax/libs/jquery/2.1.1/jquery.min.js\"></script>\n\
    <script src=\"https://maps.googleapis.com/maps/api/js?key=AIzaSyCU5S0FYwhr4fLRRCQNHI5ZkFkSdmOrFKA\"></script>\n\
    <script type=\"text/javascript\">\n\
function initialize() {\n\
    map = new google.maps.Map(document.getElementById('map-canvas'), {\n\
        mapTypeId: google.maps.MapTypeId.TERRAIN\n\
    });\n\
    map.setZoom(";
  html << zoom;
  html << ");\n\
    map.setCenter(";
  mapslatlon(html, highest);
  html << ");\n\
\n\
    rectangle = new google.maps.Rectangle({\n\
        strokeColor: '#FF0000',\n\
        strokeOpacity: 0.8,\n\
        strokeWeight: 2,\n\
        fillColor: '#FF0000',\n\
        fillOpacity: 0.35,\n\
        map: map,\n\
    });\n\
    rectangle.setBounds(new google.maps.LatLngBounds(\n\
        ";
  mapslatlon(html, start);
  html << ",\n\
        ";
  mapslatlon(html, end);
  html << "));\n\
\n";
  marker(html, highest);
  for (auto& point : visited.points_) {
    marker(html, point);
  }
  html << "}\n\
\n\
$(function () {\n\
    google.maps.event.addDomListener(window, 'load', initialize);\n\
});\n\
    </script>\n\
  </head>\n\
  <body>\n\
    <form id=\"dice\" action=\"";
  html << get_uri(hostname, uri);
  html << "\">\n";
  hidden(html, "is_lat", !is_lat);
  hidden(html, "slat", start.lat_);
  hidden(html, "slon", start.lon_);
  hidden(html, "elat", end.lat_);
  hidden(html, "elon", end.lon_);
  hidden(html, "visited", visited.String());
  hidden(html, "zoom", zoom + 1);
  hidden(html, "old_picked", new_picked);
  html << "<input type=\"text\" name=\"picked\" autofocus>\n\
        <input type=\"submit\" value=\"go\">\n\
    </form>\n\
    <a href=\"";
  html << get_link(hostname, uri, 1, Point(-90, -180), Point(90, 180), visited, 0, "");
  html << "\">reset</a>\n\
    <div id=\"info\">";
  html << highest.String();
  html << "</div>\n\
    <a href=\"";
  auto link = get_link(hostname, uri, is_lat, start, end, visited, zoom, new_picked);
  html << link << "\">" << link;
  html << "</a>\n\
    <div id=\"map-canvas\"></div>\n\
  </body>\n\
</html>\n\
     ";
  return html.str();
}

/* The sample content handler */
static int randomtrip_handler(request_rec *r)
{
  if (strcmp(r->handler, "randomtrip")) {
    return DECLINED;
  }
  r->content_type = "text/html";
  if (!r->header_only) {
    apr_table_t* GET;
    ap_args_to_table(r, &GET);
    ap_rputs(get_html(r->hostname,
                      r->uri,
                      get_int(GET, "is_lat", 1),
                      get_int(GET, "picked", 0),
                      Point(get_double(GET, "slat", -90), get_double(GET, "slon", -180)),
                      Point(get_double(GET, "elat", 90), get_double(GET, "elon", 180)),
                      get_visited(GET, "visited", Visited()),
                      get_int(GET, "zoom", 0),
                      get_string(GET, "old_picked", "")).c_str(),
             r);
  }
  return OK;
}

static void randomtrip_register_hooks(apr_pool_t *p)
{
  ap_hook_handler(randomtrip_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA randomtrip_module = {
  STANDARD20_MODULE_STUFF,
  NULL,                  /* create per-dir    config structures */
  NULL,                  /* merge  per-dir    config structures */
  NULL,                  /* create per-server config structures */
  NULL,                  /* merge  per-server config structures */
  NULL,                  /* table of config file commands       */
  randomtrip_register_hooks  /* register hooks                      */
};
