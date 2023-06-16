#include "inner.h"
// ==================== I add this
/*
 * Addition of two complex numbers (d = a + b).
 */
#define FPC_ADD(d_re, d_im, a_re, a_im, b_re, b_im) \
    d_re.v = a_re.v + b_re.v;                       \
    d_im.v = a_im.v + b_im.v;

/*
 * Addition of two complex numbers (d = a + jb).
 */
#define FPC_ADDJ(d_re, d_im, a_re, a_im, b_re, b_im) \
    d_re.v = a_re.v - b_im.v;                        \
    d_im.v = a_im.v + b_re.v;
/*
 * Subtraction of two complex numbers (d = a - b).
 */
#define FPC_SUB(d_re, d_im, a_re, a_im, b_re, b_im) \
    d_re.v = a_re.v - b_re.v;                       \
    d_im.v = a_im.v - b_im.v;

/*
 * Subtraction of two complex numbers (d = a - jb).
 */
#define FPC_SUBJ(d_re, d_im, a_re, a_im, b_re, b_im) \
    d_re.v = a_re.v + b_im.v;                        \
    d_im.v = a_im.v - b_re.v;

/*
 * Multplication of two complex numbers (d = a * b).
 */
#define FPC_MUL(d_re, d_im, a_re, a_im, b_re, b_im) \
    d_re.v = a_re.v * b_re.v - a_im.v * b_im.v;     \
    d_im.v = a_re.v * b_im.v + a_im.v * b_re.v;

/*
 * Multplication of two complex numbers (d = a * conj(b)).
 * a is swapped from: a_re|a_im to a_im|a_re
 * b is swapped from: b_re|b_im to b_im|b_re
 */
#define FPC_MUL_CONJ(d_re, d_im, a_im, a_re, b_im, b_re) \
    d_re.v = b_re.v * a_re.v + a_im.v * b_im.v;          \
    d_im.v = b_im.v * a_re.v - a_im.v * b_re.v;

/*
 * Multplication of two complex numbers (d = a * conj(jb)).
 */
#define FPC_MUL_CONJ_J(d_re, d_im, a_re, a_im, b_re, b_im) \
    d_re.v = a_im.v * b_re.v - b_im.v * a_re.v;            \
    d_im.v = -(a_im.v * b_im.v + b_re.v * a_re.v);

/*
 * Multplication of two complex numbers (d = a * - conj(jb)).
 * b is swapped from: b_re|b_im to b_im|b_re
 */
#define FPC_MUL_CONJ_J_m(d_re, d_im, a_re, a_im, b_im, b_re) \
    d_re.v = a_re.v * b_re.v - a_im.v * b_im.v;              \
    d_im.v = a_im.v * b_re.v + a_re.v * b_im.v;

const fpr fpr_tab_log2[] = {
    { 0.707106781186547524400844362}, {0.707106781186547524400844362}, // 4, 5
};

const fpr fpr_tab_log3[] = {
    { 0.923879532511286756128183189}, { 0.382683432365089771728459984}, // 8, 9
};

const fpr fpr_tab_log4[] = {
    { 0.980785280403230449126182236}, { 0.195090322016128267848284868}, // 16
    { 0.555570233019602224742830814}, { 0.831469612302545237078788378}, // 20
};

const fpr fpr_tab_log5[] = {
    { 0.995184726672196886244836953}, { 0.098017140329560601994195564}, // 32
    { 0.634393284163645498215171613}, { 0.773010453362736960810906610}, // 36
    { 0.881921264348355029712756864}, { 0.471396736825997648556387626}, // 40
    { 0.290284677254462367636192376}, { 0.956940335732208864935797887}, // 44 
};

const fpr fpr_tab_log6[] = {
    { 0.998795456205172392714771605}, { 0.049067674327418014254954977}, // 64
	{ 0.671558954847018400625376850}, { 0.740951125354959091175616897}, // 68
	{ 0.903989293123443331586200297}, { 0.427555093430282094320966857}, // 72
	{ 0.336889853392220050689253213}, { 0.941544065183020778412509403}, // 76
	{ 0.970031253194543992603984207}, { 0.242980179903263889948274162}, // 80
	{ 0.514102744193221726593693839}, { 0.857728610000272069902269984}, // 84
	{ 0.803207531480644909806676513}, { 0.595699304492433343467036529}, // 88
	{ 0.146730474455361751658850130}, { 0.989176509964780973451673738}, // 92
};

const fpr fpr_tab_log7[] = {
    { 0.999698818696204220115765650}, { 0.024541228522912288031734529}, // 128
	{ 0.689540544737066924616730630}, { 0.724247082951466920941069243}, // 132
	{ 0.914209755703530654635014829}, { 0.405241314004989870908481306}, // 136
	{ 0.359895036534988148775104572}, { 0.932992798834738887711660256}, // 140 
	{ 0.975702130038528544460395766}, { 0.219101240156869797227737547}, // 144
	{ 0.534997619887097210663076905}, { 0.844853565249707073259571205}, // 148
	{ 0.817584813151583696504920884}, { 0.575808191417845300745972454}, // 152
	{ 0.170961888760301226363642357}, { 0.985277642388941244774018433}, // 156
	{ 0.992479534598709998156767252}, { 0.122410675199216198498704474}, // 160
	{ 0.615231590580626845484913563}, { 0.788346427626606262009164705}, // 164
	{ 0.870086991108711418652292404}, { 0.492898192229784036873026689}, // 168
	{ 0.266712757474898386325286515}, { 0.963776065795439866686464356}, // 172
	{ 0.949528180593036667195936074}, { 0.313681740398891476656478846}, // 176
	{ 0.449611329654606600046294579}, { 0.893224301195515320342416447}, // 180
	{ 0.757208846506484547575464054}, { 0.653172842953776764084203014}, // 184
	{ 0.073564563599667423529465622}, { 0.997290456678690216135597140}, // 188
};

const fpr fpr_tab_log8[] = {
    { 0.999924701839144540921646491}, { 0.012271538285719926079408262}, // 256
    { 0.698376249408972853554813503}, { 0.715730825283818654125532623}, // 260
    { 0.919113851690057743908477789}, { 0.393992040061048108596188661}, // 264
    { 0.371317193951837543411934967}, { 0.928506080473215565937167396}, // 268
    { 0.978317370719627633106240097}, { 0.207111376192218549708116020}, // 272
    { 0.545324988422046422313987347}, { 0.838224705554838043186996856}, // 276
    { 0.824589302785025264474803737}, { 0.565731810783613197389765011}, // 280
    { 0.183039887955140958516532578}, { 0.983105487431216327180301155}, // 284
    { 0.993906970002356041546922813}, { 0.110222207293883058807899140}, // 288
    { 0.624859488142386377084072816}, { 0.780737228572094478301588484}, // 292
    { 0.876070094195406607095844268}, { 0.482183772079122748517344481}, // 296
    { 0.278519689385053105207848526}, { 0.960430519415565811199035138}, // 300
    { 0.953306040354193836916740383}, { 0.302005949319228067003463232}, // 304
    { 0.460538710958240023633181487}, { 0.887639620402853947760181617}, // 308
    { 0.765167265622458925888815999}, { 0.643831542889791465068086063}, // 312
    { 0.085797312344439890461556332}, { 0.996312612182778012627226190}, // 316
    { 0.998118112900149207125155861}, { 0.061320736302208577782614593}, // 320
    { 0.662415777590171761113069817}, { 0.749136394523459325469203257}, // 324
    { 0.898674465693953843041976744}, { 0.438616238538527637647025738}, // 328
    { 0.325310292162262934135954708}, { 0.945607325380521325730945387}, // 332
    { 0.966976471044852109087220226}, { 0.254865659604514571553980779}, // 336
    { 0.503538383725717558691867071}, { 0.863972856121586737918147054}, // 340
    { 0.795836904608883536262791915}, { 0.605511041404325513920626941}, // 344
    { 0.134580708507126186316358409}, { 0.990902635427780025108237011}, // 348
    { 0.987301418157858382399815802}, { 0.158858143333861441684385360}, // 352
    { 0.585797857456438860328080838}, { 0.810457198252594791726703434}, // 356
    { 0.851355193105265142261290312}, { 0.524589682678468906215098464}, // 360
    { 0.231058108280671119643236018}, { 0.972939952205560145467720114}, // 364
    { 0.937339011912574923201899593}, { 0.348418680249434568419308588}, // 368
    { 0.416429560097637182562598911}, { 0.909167983090522376563884788}, // 372
    { 0.732654271672412834615546649}, { 0.680600997795453050594430464}, // 376
    { 0.036807222941358832324332691}, { 0.999322384588349500896221011}, // 380
};

const fpr fpr_tab_log9[] = {
    { 0.999981175282601142656990438}, { 0.006135884649154475359640235}, // 512
    { 0.702754744457225302452914421}, { 0.711432195745216441522130290}, // 516
    { 0.921514039342041943465396332}, { 0.388345046698826291624993541}, // 520
    { 0.377007410216418256726567823}, { 0.926210242138311341974793388}, // 524
    { 0.979569765685440534439326110}, { 0.201104634842091911558443546}, // 528
    { 0.550457972936604802977289893}, { 0.834862874986380056304401383}, // 532
    { 0.828045045257755752067527592}, { 0.560661576197336023839710223}, // 536
    { 0.189068664149806212754997837}, { 0.981963869109555264072848154}, // 540
    { 0.994564570734255452119106243}, { 0.104121633872054579120943880}, // 544
    { 0.629638238914927025372981341}, { 0.776888465673232450040827983}, // 548
    { 0.879012226428633477831323711}, { 0.476799230063322133342158117}, // 552
    { 0.284407537211271843618310615}, { 0.958703474895871555374645792}, // 556
    { 0.955141168305770721498157712}, { 0.296150888243623824121786128}, // 560
    { 0.465976495767966177902756065}, { 0.884797098430937780104007041}, // 564
    { 0.769103337645579639346626069}, { 0.639124444863775743801488193}, // 568
    { 0.091908956497132728624990979}, { 0.995767414467659793982495643}, // 572
    { 0.998475580573294752208559038}, { 0.055195244349689939809447526}, // 576
    { 0.666999922303637506650154222}, { 0.745057785441465962407907310}, // 580
    { 0.901348847046022014570746093}, { 0.433093818853151968484222638}, // 584
    { 0.331106305759876401737190737}, { 0.943593458161960361495301445}, // 588
    { 0.968522094274417316221088329}, { 0.248927605745720168110682816}, // 592
    { 0.508830142543107036931749324}, { 0.860866938637767279344583877}, // 596
    { 0.799537269107905033500246232}, { 0.600616479383868926653875896}, // 600
    { 0.140658239332849230714788846}, { 0.990058210262297105505906464}, // 604
    { 0.988257567730749491404792538}, { 0.152797185258443427720336613}, // 608
    { 0.590759701858874228423887908}, { 0.806847553543799272206514313}, // 612
    { 0.854557988365400520767862276}, { 0.519355990165589587361829932}, // 616
    { 0.237023605994367206867735915}, { 0.971503890986251775537099622}, // 620
    { 0.939459223602189911962669246}, { 0.342660717311994397592781983}, // 624
    { 0.422000270799799685941287941}, { 0.906595704514915365332960588}, // 628
    { 0.736816568877369875090132520}, { 0.676092703575315960360419228}, // 632
    { 0.042938256934940823077124540}, { 0.999077727752645382888781997}, // 636
    { 0.999529417501093163079703322}, { 0.030674803176636625934021028}, // 640
    { 0.685083667772700381362052545}, { 0.728464390448225196492035438}, // 644
    { 0.911706032005429851404397325}, { 0.410843171057903942183466675}, // 648
    { 0.354163525420490382357395796}, { 0.935183509938947577642207480}, // 652
    { 0.974339382785575860518721668}, { 0.225083911359792835991642120}, // 656
    { 0.529803624686294668216054671}, { 0.848120344803297251279133563}, // 660
    { 0.814036329705948361654516690}, { 0.580813958095764545075595272}, // 664
    { 0.164913120489969921418189113}, { 0.986308097244598647863297524}, // 668
    { 0.991709753669099522860049931}, { 0.128498110793793172624415589}, // 672
    { 0.610382806276309452716352152}, { 0.792106577300212351782342879}, // 676
    { 0.867046245515692651480195629}, { 0.498227666972781852410983869}, // 680
    { 0.260794117915275518280186509}, { 0.965394441697689374550843858}, // 684
    { 0.947585591017741134653387321}, { 0.319502030816015677901518272}, // 688
    { 0.444122144570429231642069418}, { 0.895966249756185155914560282}, // 692
    { 0.753186799043612482483430486}, { 0.657806693297078656931182264}, // 696
    { 0.067443919563664057897972422}, { 0.997723066644191609848546728}, // 700
    { 0.996820299291165714972629398}, { 0.079682437971430121147120656}, // 704
    { 0.648514401022112445084560551}, { 0.761202385484261814029709836}, // 708
    { 0.890448723244757889952150560}, { 0.455083587126343823535869268}, // 712
    { 0.307849640041534893682063646}, { 0.951435020969008369549175569}, // 716
    { 0.962121404269041595429604316}, { 0.272621355449948984493347477}, // 720
    { 0.487550160148435954641485027}, { 0.873094978418290098636085973}, // 724
    { 0.784556597155575233023892575}, { 0.620057211763289178646268191}, // 728
    { 0.116318630911904767252544319}, { 0.993211949234794533104601012}, // 732
    { 0.984210092386929073193874387}, { 0.177004220412148756196839844}, // 736
    { 0.570780745886967280232652864}, { 0.821102514991104679060430820}, // 740
    { 0.841554977436898409603499520}, { 0.540171472729892881297845480}, // 744
    { 0.213110319916091373967757518}, { 0.977028142657754351485866211}, // 748
    { 0.930766961078983731944872340}, { 0.365612997804773870011745909}, // 752
    { 0.399624199845646828544117031}, { 0.916679059921042663116457013}, // 756
    { 0.720002507961381629076682999}, { 0.693971460889654009003734389}, // 760
    { 0.018406729905804820927366313}, { 0.999830581795823422015722275}, // 764
};

const fpr fpr_tab_log10[] = {
    { 0.999995293809576171511580126}, { 0.003067956762965976270145365}, // 1024
    { 0.704934080375904908852523758}, { 0.709272826438865651316533772}, // 1028
    { 0.922701128333878570437264227}, { 0.385516053843918864075607949}, // 1032
    { 0.379847208924051170576281147}, { 0.925049240782677590302371869}, // 1036
    { 0.980182135968117392690210009}, { 0.198098410717953586179324918}, // 1040
    { 0.553016705580027531764226988}, { 0.833170164701913186439915922}, // 1044
    { 0.829761233794523042469023765}, { 0.558118531220556115693702964}, // 1048
    { 0.192080397049892441679288205}, { 0.981379193313754574318224190}, // 1052
    { 0.994879330794805620591166107}, { 0.101069862754827824987887585}, // 1056
    { 0.632018735939809021909403706}, { 0.774953106594873878359129282}, // 1060
    { 0.880470889052160770806542929}, { 0.474100214650550014398580015}, // 1064
    { 0.287347459544729526477331841}, { 0.957826413027532890321037029}, // 1068
    { 0.956045251349996443270479823}, { 0.293219162694258650606608599}, // 1072
    { 0.468688822035827933697617870}, { 0.883363338665731594736308015}, // 1076
    { 0.771060524261813773200605759}, { 0.636761861236284230413943435}, // 1080
    { 0.094963495329638998938034312}, { 0.995480755491926941769171600}, // 1084
    { 0.998640218180265222418199049}, { 0.052131704680283321236358216}, // 1088
    { 0.669282588346636065720696366}, { 0.743007952135121693517362293}, // 1092
    { 0.902673318237258806751502391}, { 0.430326481340082633908199031}, // 1096
    { 0.333999651442009404650865481}, { 0.942573197601446879280758735}, // 1100
    { 0.969281235356548486048290738}, { 0.245955050335794611599924709}, // 1104
    { 0.511468850437970399504391001}, { 0.859301818357008404783582139}, // 1108
    { 0.801376171723140219430247777}, { 0.598160706996342311724958652}, // 1112
    { 0.143695033150294454819773349}, { 0.989622017463200834623694454}, // 1116
    { 0.988721691960323767604516485}, { 0.149764534677321517229695737}, // 1120
    { 0.593232295039799808047809426}, { 0.805031331142963597922659282}, // 1124
    { 0.856147328375194481019630732}, { 0.516731799017649881508753876}, // 1128
    { 0.240003022448741486568922365}, { 0.970772140728950302138169611}, // 1132
    { 0.940506070593268323787291309}, { 0.339776884406826857828825803}, // 1136
    { 0.424779681209108833357226189}, { 0.905296759318118774354048329}, // 1140
    { 0.738887324460615147933116508}, { 0.673829000378756060917568372}, // 1144
    { 0.046003182130914628814301788}, { 0.998941293186856850633930266}, // 1148
    { 0.999618822495178597116830637}, { 0.027608145778965741612354872}, // 1152
    { 0.687315340891759108199186948}, { 0.726359155084345976817494315}, // 1156
    { 0.912962190428398164628018233}, { 0.408044162864978680820747499}, // 1160
    { 0.357030961233430032614954036}, { 0.934092550404258914729877883}, // 1164
    { 0.975025345066994146844913468}, { 0.222093620973203534094094721}, // 1168
    { 0.532403127877197971442805218}, { 0.846490938774052078300544488}, // 1172
    { 0.815814410806733789010772660}, { 0.578313796411655563342245019}, // 1176
    { 0.167938294974731178054745536}, { 0.985797509167567424700995000}, // 1180
    { 0.992099313142191757112085445}, { 0.125454983411546238542336453}, // 1184
    { 0.612810082429409703935211936}, { 0.790230221437310055030217152}, // 1188
    { 0.868570705971340895340449876}, { 0.495565261825772531150266670}, // 1192
    { 0.263754678974831383611349322}, { 0.964589793289812723836432159}, // 1196
    { 0.948561349915730288158494826}, { 0.316593375556165867243047035}, // 1200
    { 0.446868840162374195353044389}, { 0.894599485631382678433072126}, // 1204
    { 0.755201376896536527598710756}, { 0.655492852999615385312679701}, // 1208
    { 0.070504573389613863027351471}, { 0.997511456140303459699448390}, // 1212
    { 0.997060070339482978987989949}, { 0.076623861392031492278332463}, // 1216
    { 0.650846684996380915068975573}, { 0.759209188978388033485525443}, // 1220
    { 0.891840709392342727796478697}, { 0.452349587233770874133026703}, // 1224
    { 0.310767152749611495835997250}, { 0.950486073949481721759926101}, // 1228
    { 0.962953266873683886347921481}, { 0.269668325572915106525464462}, // 1232
    { 0.490226483288291154229598449}, { 0.871595086655951034842481435}, // 1236
    { 0.786455213599085757522319464}, { 0.617647307937803932403979402}, // 1240
    { 0.119365214810991364593637790}, { 0.992850414459865090793563344}, // 1244
    { 0.984748501801904218556553176}, { 0.173983873387463827950700807}, // 1248
    { 0.573297166698042212820171239}, { 0.819347520076796960824689637}, // 1252
    { 0.843208239641845437161743865}, { 0.537587076295645482502214932}, // 1256
    { 0.216106797076219509948385131}, { 0.976369731330021149312732194}, // 1260
    { 0.931884265581668106718557199}, { 0.362755724367397216204854462}, // 1264
    { 0.402434650859418441082533934}, { 0.915448716088267819566431292}, // 1268
    { 0.722128193929215321243607198}, { 0.691759258364157774906734132}, // 1272
    { 0.021474080275469507418374898}, { 0.999769405351215321657617036}, // 1276
    { 0.999882347454212525633049627}, { 0.015339206284988101044151868}, // 1280
    { 0.696177131491462944788582591}, { 0.717870045055731736211325329}, // 1284
    { 0.917900775621390457642276297}, { 0.396809987416710328595290911}, // 1288
    { 0.368466829953372331712746222}, { 0.929640895843181265457918066}, // 1292
    { 0.977677357824509979943404762}, { 0.210111836880469621717489972}, // 1296
    { 0.542750784864515906586768661}, { 0.839893794195999504583383987}, // 1300
    { 0.822849781375826332046780034}, { 0.568258952670131549790548489}, // 1304
    { 0.180022901405699522679906590}, { 0.983662419211730274396237776}, // 1308
    { 0.993564135520595333782021697}, { 0.113270952177564349018228733}, // 1312
    { 0.622461279374149972519166721}, { 0.782650596166575738458949301}, // 1316
    { 0.874586652278176112634431897}, { 0.484869248000791101822951699}, // 1320
    { 0.275571819310958163076425168}, { 0.961280485811320641748659653}, // 1324
    { 0.952375012719765858529893608}, { 0.304929229735402406490728633}, // 1328
    { 0.457813303598877221904961155}, { 0.889048355854664562540777729}, // 1332
    { 0.763188417263381271704838297}, { 0.646176012983316364832802220}, // 1336
    { 0.082740264549375693111987083}, { 0.996571145790554847093566910}, // 1340
    { 0.997925286198596012623025462}, { 0.064382630929857460819324537}, // 1344
    { 0.660114342067420478559490747}, { 0.751165131909686411205819422}, // 1348
    { 0.897324580705418281231391836}, { 0.441371268731716692879988968}, // 1352
    { 0.322407678801069848384807478}, { 0.946600913083283570044599823}, // 1356
    { 0.966190003445412555433832961}, { 0.257831102162159005614471295}, // 1360
    { 0.500885382611240786241285004}, { 0.865513624090569082825488358}, // 1364
    { 0.793975477554337164895083757}, { 0.607949784967773667243642671}, // 1368
    { 0.131540028702883111103387493}, { 0.991310859846115418957349799}, // 1372
    { 0.986809401814185476970235952}, { 0.161886393780111837641387995}, // 1376
    { 0.583308652937698294392830961}, { 0.812250586585203913049744181}, // 1380
    { 0.849741768000852489471268395}, { 0.527199134781901348464274575}, // 1384
    { 0.228072083170885739254457379}, { 0.973644249650811925318383912}, // 1388
    { 0.936265667170278246576310996}, { 0.351292756085567125601307623}, // 1392
    { 0.413638312238434547471944324}, { 0.910441292258067196934095369}, // 1396
    { 0.730562769227827561177758850}, { 0.682845546385248068164596123}, // 1400
    { 0.033741171851377584833716112}, { 0.999430604555461772019008327}, // 1404
    { 0.999204758618363895492950001}, { 0.039872927587739811128578738}, // 1408
    { 0.678350043129861486873655042}, { 0.734738878095963464563223604}, // 1412
    { 0.907886116487666212038681480}, { 0.419216888363223956433010020}, // 1416
    { 0.345541324963989065539191723}, { 0.938403534063108112192420774}, // 1420
    { 0.972226497078936305708321144}, { 0.234041958583543423191242045}, // 1424
    { 0.521975292937154342694258318}, { 0.852960604930363657746588082}, // 1428
    { 0.808656181588174991946968128}, { 0.588281548222645304786439813}, // 1432
    { 0.155828397654265235743101486}, { 0.987784141644572154230969032}, // 1436
    { 0.990485084256457037998682243}, { 0.137620121586486044948441663}, // 1440
    { 0.603066598540348201693430617}, { 0.797690840943391108362662755}, // 1444
    { 0.862423956111040538690933878}, { 0.506186645345155291048942344}, // 1448
    { 0.251897818154216950498106628}, { 0.967753837093475465243391912}, // 1452
    { 0.944604837261480265659265493}, { 0.328209843579092526107916817}, // 1456
    { 0.435857079922255491032544080}, { 0.900015892016160228714535267}, // 1460
    { 0.747100605980180144323078847}, { 0.664710978203344868130324985}, // 1464
    { 0.058258264500435759613979782}, { 0.998301544933892840738782163}, // 1468
    { 0.996044700901251989887944810}, { 0.088853552582524596561586535}, // 1472
    { 0.641481012808583151988739898}, { 0.767138911935820381181694573}, // 1476
    { 0.886222530148880631647990821}, { 0.463259783551860197390719637}, // 1480
    { 0.299079826308040476750336973}, { 0.954228095109105629780430732}, // 1484
    { 0.959571513081984528335528181}, { 0.281464937925757984095231007}, // 1488
    { 0.479493757660153026679839798}, { 0.877545290207261291668470750}, // 1492
    { 0.778816512381475953374724325}, { 0.627251815495144113509622565}, // 1496
    { 0.107172424956808849175529148}, { 0.994240449453187946358413442}, // 1500
    { 0.982539302287441255907040396}, { 0.186055151663446648105438304}, // 1504
    { 0.563199344013834115007363772}, { 0.826321062845663480311195452}, // 1508
    { 0.836547727223511984524285790}, { 0.547894059173100165608820571}, // 1512
    { 0.204108966092816874181696950}, { 0.978948175319062194715480124}, // 1516
    { 0.927362525650401087274536959}, { 0.374164062971457997104393020}, // 1520
    { 0.391170384302253888687512949}, { 0.920318276709110566440076541}, // 1524
    { 0.713584868780793592903125099}, { 0.700568793943248366792866380}, // 1528
    { 0.009203754782059819315102378}, { 0.999957644551963866333120920}, // 1532
};


// void split_fwd_FFT(fpr *f, unsigned logn)
void
Zf(FFT)(fpr *f, unsigned logn)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;
    const unsigned ht = n >> 2;
    unsigned len, start, j, k;
    fpr zeta_re, zeta_im, t_re, t_im, a_re, a_im, b_re, b_im;

    /*
     * We read the twiddle table in forward order
     */
    int level = 1;
    const fpr *fpr_tab = NULL;
    const fpr *table[] = {
        fpr_tab_log2,
        fpr_tab_log3,
        fpr_tab_log4,
        fpr_tab_log5,
        fpr_tab_log6,
        fpr_tab_log7,
        fpr_tab_log8,
        fpr_tab_log9,
        fpr_tab_log10};

    fpr_tab = table[0];
    zeta_re = fpr_tab[0];
    zeta_im = fpr_tab[1];

    for (j = 0; j < ht; j += 1)
    {
        a_re = f[j];
        a_im = f[j + hn];
        b_re = f[j + ht];
        b_im = f[j + ht + hn];

        FPC_MUL(t_re, t_im, b_re, b_im, zeta_re, zeta_im);
        FPC_SUB(f[j + ht], f[j + ht + hn], a_re, a_im, t_re, t_im);
        FPC_ADD(f[j], f[j + hn], a_re, a_im, t_re, t_im);
    }

    for (len = ht / 2; len > 0; len >>= 1)
    {
        fpr_tab = table[level++];
        k = 0;
        for (start = 0; start < hn; start = j + len)
        {
            zeta_re = fpr_tab[k];
            zeta_im = fpr_tab[k + 1];
            k += 2;
            for (j = start; j < start + len; j += 1)
            {
                a_re = f[j];
                a_im = f[j + hn];
                b_re = f[j + len];
                b_im = f[j + len + hn];

                FPC_MUL(t_re, t_im, b_re, b_im, zeta_re, zeta_im);
                FPC_SUB(f[j + len], f[j + len + hn], a_re, a_im, t_re, t_im);
                FPC_ADD(f[j], f[j + hn], a_re, a_im, t_re, t_im);
            }

            start = j + len;

            for (j = start; j < start + len; j += 1)
            {
                a_re = f[j];
                a_im = f[j + hn];
                b_re = f[j + len];
                b_im = f[j + len + hn];

                FPC_MUL(t_re, t_im, b_re, b_im, zeta_re, zeta_im);
                FPC_SUBJ(f[j + len], f[j + len + hn], a_re, a_im, t_re, t_im);
                FPC_ADDJ(f[j], f[j + hn], a_re, a_im, t_re, t_im);
            }
        }
    }
}

// void split_inv_FFT(fpr *f, unsigned logn)
void
Zf(iFFT)(fpr *f, unsigned logn)
{
    const unsigned n = 1 << logn;
    const unsigned hn = n >> 1;
    const unsigned ht = n >> 2;
    unsigned len, start, j, k;
    fpr zeta_re, zeta_im, t_re, t_im, a_re, a_im, b_re, b_im;

    /*
     * This time we read the table in reverse order,
     * so the pointer point to the end of the table
     */
    int level = logn - 2;
    const fpr *fpr_tab_inv = NULL;
    const fpr *table[] = {
        fpr_tab_log2,
        fpr_tab_log3,
        fpr_tab_log4,
        fpr_tab_log5,
        fpr_tab_log6,
        fpr_tab_log7,
        fpr_tab_log8,
        fpr_tab_log9,
        fpr_tab_log10,
    };

    for (len = 1; len < ht; len <<= 1)
    {
        fpr_tab_inv = table[level--];
        k = 0;

        for (start = 0; start < hn; start = j + len)
        {
            // Conjugate of zeta is embeded in MUL
            zeta_re = fpr_tab_inv[k];
            zeta_im = fpr_tab_inv[k + 1];
            k += 2;

            for (j = start; j < start + len; j += 1)
            {
                a_re = f[j];
                a_im = f[j + hn];
                b_re = f[j + len];
                b_im = f[j + len + hn];

                FPC_ADD(f[j], f[j + hn], a_re, a_im, b_re, b_im);
                FPC_SUB(t_re, t_im, a_re, a_im, b_re, b_im);
                FPC_MUL_CONJ(f[j + len], f[j + len + hn], t_re, t_im, zeta_re, zeta_im);
            }

            start = j + len;

            for (j = start; j < start + len; j += 1)
            {
                a_re = f[j];
                a_im = f[j + hn];
                b_re = f[j + len];
                b_im = f[j + len + hn];

                /*
                 * Notice we swap the (a - b) to (b - a) in FPC_SUB
                 */
                FPC_ADD(f[j], f[j + hn], a_re, a_im, b_re, b_im);
                FPC_SUB(t_re, t_im, b_re, b_im, a_re, a_im);
                FPC_MUL_CONJ_J_m(f[j + len], f[j + len + hn], t_re, t_im, zeta_re, zeta_im);
            }
        }
    }

    fpr_tab_inv = table[0];
    zeta_re.v = fpr_tab_inv[0].v * fpr_p2_tab[logn].v;
    zeta_im.v = fpr_tab_inv[1].v * fpr_p2_tab[logn].v;

    for (j = 0; j < ht; j += 1)
    {
        a_re = f[j];
        a_im = f[j + hn];
        b_re = f[j + ht];
        b_im = f[j + ht + hn];

        FPC_ADD(f[j], f[j + hn], a_re, a_im, b_re, b_im);
        FPC_SUB(t_re, t_im, a_re, a_im, b_re, b_im);
        FPC_MUL_CONJ(f[j + ht], f[j + ht + hn], t_re, t_im, zeta_re, zeta_im);

        f[j].v *= fpr_p2_tab[logn].v;
        f[j + hn].v *= fpr_p2_tab[logn].v;
    }
}
