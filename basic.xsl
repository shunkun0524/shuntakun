<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
  <xsl:template match="/">
    <xsl:apply-templates/>
  </xsl:template>
  <xsl:template match="member"> 
    <html><xsl:apply-templates/></html>
  </xsl:template>
  <xsl:template match="name" > 
    <p><xsl:value-of select="."/></p>
  </xsl:template>
  <xsl:template match="age" > 
    <p><xsl:value-of select="."/></p>
  </xsl:template>
  <xsl:template match="uro">
    <a href="https://cclms.kyoto-su.ac.jp"><xsl:value-of select="."/></a>
  </xsl:template>
  <xsl:template match="gazo">
    <img src="iii.jpg" width="300" height="300">
    </img>
  </xsl:template>
</xsl:stylesheet>
