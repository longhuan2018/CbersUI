TEMPLATE = subdirs
SUBDIRS = CbersUI x3py CbersPluginCore CbersApp plugins
CbersApp.depends = CbersUI CbersPluginCore plugins
CbersPluginCore.depends = x3py
plugins.depends = CbersPluginCore
