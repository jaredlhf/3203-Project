<?xml-stylesheet type="text/xsl" href="analysis.xsl"?>
<test_results>
<info>
<name>Tests25</name><parsing_time_taken>4.111000</parsing_time_taken>
</info>
<queries>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">1</id><querystr><![CDATA[stmt s; Select s such that Next*(1, 2)]]></querystr>
<stuans>1,10,11,12,13,14,15,16,17,18,19,2,20,3,4,5,6,7,8,9</stuans>
<correct>1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20</correct>
<time_taken>1.690000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">2</id><querystr><![CDATA[assign a; Select a such that Next*(5, 6)]]></querystr>
<stuans></stuans>
<correct></correct>
<time_taken>0.867000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">3</id><querystr><![CDATA[stmt s; Select s such that Next*(4, 3)]]></querystr>
<stuans></stuans>
<correct></correct>
<time_taken>0.927000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">4</id><querystr><![CDATA[print pr; Select pr such that Next*(1, pr)]]></querystr>
<stuans>10,18,19,20,5,8</stuans>
<correct>5,8,10,18,19,20</correct>
<time_taken>1.355000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">5</id><querystr><![CDATA[stmt s; Select s such that Next*(1, s)]]></querystr>
<stuans>10,11,12,13,14,15,16,17,18,19,2,20,3,4,5,6,7,8,9</stuans>
<correct>2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20</correct>
<time_taken>2.650000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="NextStar">6</id><querystr><![CDATA[procedure p; Select p such that Next*(1, _)]]></querystr>
<stuans>NextStarTest</stuans>
<correct>NextStarTest</correct>
<time_taken>0.848000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="NextStar">7</id><querystr><![CDATA[stmt s; Select s such that Next*(20, _)]]></querystr>
<stuans></stuans>
<correct></correct>
<time_taken>0.861000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="NextStar">8</id><querystr><![CDATA[stmt s; Select s such that Next*(1000, _)]]></querystr>
<stuans></stuans>
<correct></correct>
<time_taken>0.910000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">9</id><querystr><![CDATA[stmt s1, s2; Select s1 such that Next*(s1, s2)]]></querystr>
<stuans>1,10,11,12,13,14,15,16,17,18,19,2,3,4,5,6,7,8,9</stuans>
<correct>1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19</correct>
<time_taken>21.096000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">10</id><querystr><![CDATA[stmt s; Select s such that Next*(s, s)]]></querystr>
<stuans>12,13,14,15,16,17,18</stuans>
<correct>12,13,14,15,16,17,18</correct>
<time_taken>12.871000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">11</id><querystr><![CDATA[stmt s1, s2; Select s2 such that Next*(s1, s2)]]></querystr>
<stuans>10,11,12,13,14,15,16,17,18,19,2,20,3,4,5,6,7,8,9</stuans>
<correct>2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20</correct>
<time_taken>21.025000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">12</id><querystr><![CDATA[stmt s; if ifs; Select s such that Next*(s, ifs)]]></querystr>
<stuans>1,2,3,4,6</stuans>
<correct>1,2,3,4,6</correct>
<time_taken>3.510000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="NextStar">13</id><querystr><![CDATA[stmt s; Select s such that Next*(s, _)]]></querystr>
<stuans>1,10,11,12,13,14,15,16,17,18,19,2,3,4,5,6,7,8,9</stuans>
<correct>1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19</correct>
<time_taken>2.588000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="NextStar">14</id><querystr><![CDATA[print pr; Select pr such that Next*(pr, _)]]></querystr>
<stuans>10,18,19,5,8</stuans>
<correct>5,8,10,18,19</correct>
<time_taken>1.172000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="NextStar">15</id><querystr><![CDATA[call cl; Select cl such that Next*(cl, _)]]></querystr>
<stuans></stuans>
<correct></correct>
<time_taken>0.849000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">16</id><querystr><![CDATA[stmt s; Select s such that Next*(s, 10)]]></querystr>
<stuans>1,2,3,4,5,6,7,8,9</stuans>
<correct>1,2,3,4,5,6,7,8,9</correct>
<time_taken>1.752000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">17</id><querystr><![CDATA[assign a; Select a such that Next*(a, 12)]]></querystr>
<stuans>1,11,13,15,17,3,6,9</stuans>
<correct>1,3,6,9,11,13,15,17</correct>
<time_taken>1.499000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">18</id><querystr><![CDATA[stmt s; Select s such that Next*(s, 1)]]></querystr>
<stuans></stuans>
<correct></correct>
<time_taken>0.915000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="NextStar">19</id><querystr><![CDATA[stmt s; Select s such that Next*(_, s)]]></querystr>
<stuans>10,11,12,13,14,15,16,17,18,19,2,20,3,4,5,6,7,8,9</stuans>
<correct>2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20</correct>
<time_taken>2.195000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="NextStar">20</id><querystr><![CDATA[while w; Select w such that Next*(_, w)]]></querystr>
<stuans>12,14,16</stuans>
<correct>12,14,16</correct>
<time_taken>0.967000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="NextStar">21</id><querystr><![CDATA[procedure p; Select p such that Next*(_, 2)]]></querystr>
<stuans>NextStarTest</stuans>
<correct>NextStarTest</correct>
<time_taken>0.851000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="NextStar">22</id><querystr><![CDATA[stmt s; Select s such that Next*(_, 1)]]></querystr>
<stuans></stuans>
<correct></correct>
<time_taken>0.957000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="NextStar">23</id><querystr><![CDATA[stmt s; Select s such that Next*(_, 100)]]></querystr>
<stuans></stuans>
<correct></correct>
<time_taken>0.959000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="NextStar">24</id><querystr><![CDATA[print pr; Select pr such that Next*(_, _)]]></querystr>
<stuans>10,18,19,20,5,8</stuans>
<correct>5,8,10,18,19,20</correct>
<time_taken>0.951000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="NextStar">25</id><querystr><![CDATA[stmt s; Select s such that Next*(_, _)]]></querystr>
<stuans>1,10,11,12,13,14,15,16,17,18,19,2,20,3,4,5,6,7,8,9</stuans>
<correct>1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20</correct>
<time_taken>1.397000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">26</id><querystr><![CDATA[stmt that, Select; Select that such that Next*(that, Select)]]></querystr>
<stuans>1,10,11,12,13,14,15,16,17,18,19,2,3,4,5,6,7,8,9</stuans>
<correct>1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19</correct>
<time_taken>21.208000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">27</id><querystr><![CDATA[stmt that, Select; Select Select such that Next*(that, Select)]]></querystr>
<stuans>10,11,12,13,14,15,16,17,18,19,2,20,3,4,5,6,7,8,9</stuans>
<correct>2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20</correct>
<time_taken>22.206000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="2" CondNum="4" RelNum="1" comment="NextStar">28</id><querystr><![CDATA[print such, that; Select such such that Next*(such, that)]]></querystr>
<stuans>10,18,19,5,8</stuans>
<correct>5,8,10,18,19</correct>
<time_taken>1.962000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">29</id><querystr><![CDATA[while that, such; Select that such that Next*(such, that)]]></querystr>
<stuans>12,14,16</stuans>
<correct>12,14,16</correct>
<time_taken>1.301000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">30</id><querystr><![CDATA[stmt s; if ifs; Select s      such that    Next*(s, ifs)]]></querystr>
<stuans>1,2,3,4,6</stuans>
<correct>1,2,3,4,6</correct>
<time_taken>3.018000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">31</id><querystr><![CDATA[stmt s; Select s such that Next*( , )]]></querystr>
<stuans>SyntaxError</stuans>
<correct>SyntaxError</correct>
<time_taken>0.717000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">32</id><querystr><![CDATA[stmt s; Select s such that Next*(s, )]]></querystr>
<stuans>SyntaxError</stuans>
<correct>SyntaxError</correct>
<time_taken>0.734000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">33</id><querystr><![CDATA[stmt s1, s2; Select s1 such that Next*( , s2)]]></querystr>
<stuans>SyntaxError</stuans>
<correct>SyntaxError</correct>
<time_taken>0.714000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">34</id><querystr><![CDATA[procedure p; stmt s; Select s such that Next*(p, s)]]></querystr>
<stuans>SemanticError</stuans>
<correct>SemanticError</correct>
<time_taken>0.897000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">35</id><querystr><![CDATA[procedure p; stmt s; Select s such that Next*(s, p)]]></querystr>
<stuans>SemanticError</stuans>
<correct>SemanticError</correct>
<time_taken>0.879000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">36</id><querystr><![CDATA[stmt s; Select s such that Next*(s, "")]]></querystr>
<stuans>SyntaxError</stuans>
<correct>SyntaxError</correct>
<time_taken>0.722000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Nextstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="NextStar">37</id><querystr><![CDATA[stmt s; Select s1 such that Next*(s1, 2)]]></querystr>
<stuans>SemanticError</stuans>
<correct>SemanticError</correct>
<time_taken>0.755000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" SuchThat="1" CondNum="2" RelNum="0" comment="NextStar">38</id><querystr><![CDATA[stmt s1, s2; Select s1 such that Nxt(s1, s2)]]></querystr>
<stuans>SyntaxError</stuans>
<correct>SyntaxError</correct>
<time_taken>0.738000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" SuchThat="1" CondNum="2" RelNum="0" comment="NextStar">39</id><querystr><![CDATA[stmt s1, s2; Select s1 such that next(s1, s2)]]></querystr>
<stuans>SyntaxError</stuans>
<correct>SyntaxError</correct>
<time_taken>0.723000</time_taken>
<passed/>
</query>
</queries>
</test_results>
