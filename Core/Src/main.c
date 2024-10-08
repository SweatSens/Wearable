/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim7;

/* USER CODE BEGIN PV */
uint8_t SPI_tx_flag = 1;
uint8_t sec_flag = 0;
struct settings_swv swv1 = {
		.t_equilibration = 5.0,
		.E_begin = -0.5,
		.E_end = 1.5,
		.E_step = 0.005,
		.Amplitude = 0.025,
		.Frequency = 10.0,
};
uint8_t USB_buffer[3000];
float buf_float[300];

// use =TEXTJOIN(",",TRUE,A3:A260) from excel to put data in array
struct voltammogram v1 = {
		.length  = 258,
		.I = {0.0625,0.110118821263313,0.10741038620472,0.10533132404089,0.104129694402218,0.102455995976925,0.101759813725948,0.100253008306026,0.0995472893118858,0.0982645973563194,0.0974730476737022,0.0961903557181358,0.0958327278494835,0.094845674932003,0.0939539894461632,0.092952586710453,0.0919369235634804,0.0914839282631874,0.0903013721108437,0.0896719470620155,0.0882557407021523,0.0877789035439491,0.086686946451664,0.0858477130532265,0.0850275531411171,0.0839308276772499,0.0832775607705116,0.082271434366703,0.0816467776894569,0.0801399275660515,0.0799873396754265,0.0787761732935905,0.0779083296656609,0.0771310850977898,0.0764205977320671,0.0757673308253288,0.0750902220606804,0.0748518034815788,0.0737836882472038,0.0737073943018913,0.0729682967066765,0.0717952772974968,0.0712898299098015,0.0714567229151726,0.0699642226099968,0.0697830244898796,0.0692918822169304,0.0694826170802116,0.0688722655177116,0.0684382915496826,0.0682141780853271,0.0680031776428223,0.0676276683807373,0.067732572555542,0.0672128200531006,0.066669225692749,0.0666930675506592,0.0662162303924561,0.0673272609710693,0.0668599605560303,0.0661876201629639,0.0663354396820068,0.0666072368621826,0.0667169094085693,0.0668981075286865,0.0672843456268311,0.0669314861297607,0.0673367977142334,0.0673415660858154,0.0680711269378662,0.0676848888397217,0.0683190822601318,0.0682666301727295,0.0692680403590202,0.0694778487086296,0.0699403807520866,0.0703933760523796,0.0711801573634148,0.071523480117321,0.0719526335597038,0.0727632567286491,0.0743272826075554,0.0744798704981804,0.0755527541041374,0.0764444395899773,0.0775697752833366,0.0783708617091179,0.0798633620142937,0.0806119963526726,0.0826242938637733,0.0840452685952187,0.0850466266274452,0.0864819064736366,0.0876883044838905,0.0892952457070351,0.0914028659462929,0.0932625308632851,0.0949315056204796,0.096824549138546,0.0987128242850304,0.100367449223995,0.10258474200964,0.104449175298214,0.107582047581673,0.109456017613411,0.112688973546028,0.114596322178841,0.117519333958626,0.120475769042969,0.122697830200195,0.127289772033691,0.130846977233887,0.135105177760124,0.13941578567028,0.144689664244652,0.149605855345726,0.155308827757835,0.161998897790909,0.167573124170303,0.175255015492439,0.182526782155037,0.189379021525383,0.197222992777824,0.204890534281731,0.213178068399429,0.222137838602066,0.230987936258316,0.240295886993408,0.249656200408936,0.260451793670654,0.269926637411118,0.280507653951645,0.291737288236618,0.303872793912888,0.316118061542511,0.328911602497101,0.342244058847427,0.356739908456802,0.369976997375488,0.385931968688965,0.402139753103256,0.419212818145752,0.437380313873291,0.455500602722168,0.475003242492676,0.493599891662598,0.514771461486816,0.535037040710449,0.558259010314941,0.580098628997803,0.601890087127686,0.623776912689209,0.64532995223999,0.664498805999756,0.684430599212646,0.703838348388672,0.721624374389648,0.737693786621094,0.751235961914062,0.763967514038086,0.771978378295898,0.780704498291016,0.787570953369141,0.793817520141602,0.797060012817383,0.799444198608398,0.80120849609375,0.799253463745117,0.802066802978516,0.802639007568359,0.805023193359375,0.807598114013672,0.810506820678711,0.813797473907471,0.817135334014893,0.818184375762939,0.821426868438721,0.82290506362915,0.823429584503174,0.822762012481689,0.820759296417236,0.815847873687744,0.809791564941406,0.803497314453125,0.797298431396484,0.792625427246094,0.786188125610352,0.781515121459961,0.777605056762695,0.77522087097168,0.773456573486328,0.773838043212891,0.777414321899414,0.782087326049805,0.788333892822266,0.796487808227539,0.805690765380859,0.816324710845947,0.828341007232666,0.842216968536377,0.85795259475708,0.874451160430908,0.891664981842041,0.909594058990479,0.928762912750244,0.946310997009277,0.96652889251709,0.987700462341309,1.00868129730225,1.03052043914795,1.05288410186768,1.07644033432007,1.09889936447144,1.12355184555054,1.14844274520874,1.17710065841675,1.2038516998291,1.23227119445801,1.26164436340332,1.29178047180176,1.31886529922485,1.35167169570923,1.38471651077271,1.41871500015259,1.45233249664307,1.48790454864502,1.52376270294189,1.55823802947998,1.59390592575073,1.63167142868042,1.67267942428589,1.71149444580078,1.75150108337402,1.79184150695801,1.83404159545898,1.87085342407227,1.91486644744873,1.95897388458252,2.00417804718018,2.04799938201904,2.09430027008057,2.14117431640625,2.18656921386719,2.23601722717285,2.28694343566895,2.34330558776855,2.39871501922607,2.45555400848389,2.50602722167969,2.60377883911133,2.64144897460937,2.71154403686523,2.78640747070312,2.86413192749023,2.94519424438477,3.03102493286133,3.12353134155273,3.21365833282471},
		.U = {-0.0949611663818359,-0.0898828506469727,-0.0848827362060547,-0.0798053741455078,-0.0748052597045898,-0.0698051452636719,-0.0647268295288086,-0.0597267150878906,-0.0546483993530273,-0.0496482849121094,-0.0445699691772461,-0.0395708084106445,-0.0344924926757812,-0.0294923782348633,-0.0244140625,-0.019413948059082,-0.0144138336181641,-0.00933551788330078,-0.00433635711669922,0.000741958618164062,0.00574207305908203,0.0108203887939453,0.0158205032348633,0.0208988189697266,0.0258989334106445,0.0309762954711914,0.0359764099121094,0.0409765243530273,0.0460548400878906,0.0510549545288086,0.0561332702636719,0.0611333847045898,0.0662117004394531,0.0712108612060547,0.076289176940918,0.0812892913818359,0.0862894058227539,0.0913677215576172,0.0963678359985352,0.101446151733398,0.1064453125,0.111523628234863,0.116523742675781,0.121602058410645,0.126602172851562,0.131680488586426,0.136680603027344,0.141680717468262,0.146758079528809,0.151758193969727,0.15683650970459,0.161836624145508,0.166914939880371,0.171915054321289,0.176993370056152,0.181992530822754,0.187070846557617,0.192070960998535,0.197071075439453,0.202149391174316,0.207149505615234,0.212227821350098,0.217226982116699,0.222305297851562,0.22730541229248,0.232383728027344,0.237383842468262,0.242462158203125,0.247462272644043,0.252462387084961,0.257539749145508,0.262539863586426,0.267618179321289,0.272618293762207,0.27769660949707,0.282696723937988,0.287775039672852,0.292774200439453,0.297852516174316,0.302852630615234,0.307852745056152,0.312931060791016,0.317931175231934,0.323009490966797,0.328008651733398,0.333086967468262,0.33808708190918,0.343165397644043,0.348165512084961,0.353243827819824,0.358243942260742,0.36324405670166,0.368321418762207,0.373321533203125,0.378399848937988,0.383399963378906,0.38847827911377,0.393478393554687,0.398556709289551,0.403555870056152,0.40855598449707,0.413634300231934,0.418634414672852,0.423712730407715,0.428712844848633,0.433791160583496,0.438790321350098,0.443868637084961,0.448868751525879,0.453947067260742,0.45894718170166,0.463947296142578,0.469025611877441,0.474025726318359,0.479103088378906,0.484103202819824,0.489181518554687,0.494181632995605,0.499259948730469,0.504260063171387,0.50933837890625,0.514337539672852,0.51933765411377,0.524415969848633,0.529416084289551,0.534494400024414,0.539494514465332,0.544572830200195,0.549571990966797,0.55465030670166,0.559650421142578,0.564728736877441,0.569728851318359,0.574728965759277,0.579807281494141,0.584807395935059,0.589884757995605,0.594884872436523,0.599963188171387,0.604963302612305,0.610041618347168,0.615041732788086,0.620120048522949,0.625119209289551,0.630119323730469,0.635197639465332,0.64019775390625,0.645276069641113,0.650276184082031,0.655354499816895,0.660353660583496,0.665431976318359,0.670432090759277,0.675510406494141,0.680510520935059,0.685510635375977,0.69058895111084,0.695589065551758,0.700666427612305,0.705666542053223,0.710744857788086,0.715744972229004,0.720823287963867,0.725823402404785,0.730823516845703,0.73590087890625,0.740900993347168,0.745979309082031,0.750979423522949,0.756057739257812,0.76105785369873,0.766136169433594,0.771135330200195,0.776213645935059,0.781213760375977,0.786213874816895,0.791292190551758,0.796292304992676,0.801370620727539,0.806370735168457,0.811448097229004,0.816448211669922,0.821526527404785,0.826526641845703,0.831604957580566,0.836605072021484,0.841605186462402,0.846682548522949,0.851682662963867,0.85676097869873,0.861761093139648,0.866839408874512,0.87183952331543,0.876917839050293,0.881916999816895,0.886995315551758,0.891995429992676,0.896995544433594,0.902073860168457,0.907073974609375,0.912152290344238,0.917152404785156,0.922229766845703,0.927229881286621,0.932308197021484,0.937308311462402,0.942386627197266,0.947386741638184,0.952386856079102,0.957464218139648,0.962464332580566,0.96754264831543,0.972542762756348,0.977621078491211,0.982621192932129,0.987699508666992,0.992698669433594,0.997776985168457,1.00277709960937,1.00777721405029,1.01285552978516,1.01785564422607,1.02293395996094,1.02793407440186,1.0330114364624,1.03801155090332,1.04308986663818,1.0480899810791,1.05309009552002,1.05816841125488,1.0631685256958,1.06824588775635,1.07324600219727,1.07832431793213,1.08332443237305,1.08840274810791,1.09340286254883,1.09848117828369,1.10348033905029,1.10848045349121,1.11355876922607,1.11855888366699,1.12363719940186,1.12863731384277,1.13371562957764,1.13871574401855,1.1437931060791,1.14879322052002,1.15387153625488,1.1588716506958,1.16387176513672,1.16895008087158,1.1739501953125,1.17902755737305,1.18402767181396,1.18910598754883,1.19410610198975,1.19918441772461},
		.peakI = 0,
		.peakU = 0,
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM7_Init(void);
/* USER CODE BEGIN PFP */
float USB_data(float num);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_DEVICE_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  uint8_t I2C_addrss = 0b10010000;
  uint8_t I2C_tx_data[1];
  uint8_t I2C_rx_data[2];
  int16_t I2C_temp = 0;
  float temp = 0.0;

  // disable internal reference DAC's
  HAL_GPIO_WritePin(GPIOA, EN_4_2VDC_Pin, GPIO_PIN_SET);
  write_DAC(CONFIG, 0x0100);
  write_DAC(0x04, 0x0103);
  HAL_GPIO_WritePin(GPIOB, EN_REF_Pin, GPIO_PIN_SET);
  // DAC1 set value at 0
  DAC_set(CH0, 0.00);
  DAC_set(CH1, 0.00);

  USB_buffer[0] = 82;
  uint32_t set_cntr = 60;
  uint32_t cntr = set_cntr;
  uint8_t use_measurement = 0;
  uint8_t run_algorithms = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  if(sec_flag == 1){

		  // get temperature
		  I2C_tx_data[0] = 0x01;
		  HAL_I2C_Master_Transmit(&hi2c1, I2C_addrss, I2C_tx_data, 1, 100);
		  HAL_I2C_Master_Receive(&hi2c1, I2C_addrss, I2C_rx_data, 2, 100);
		  if((I2C_rx_data[1]&0x20) == 0x20){
			  I2C_tx_data[0] = 0x00;
			  HAL_I2C_Master_Transmit(&hi2c1, I2C_addrss, I2C_tx_data, 1, 100);
			  HAL_I2C_Master_Receive(&hi2c1, I2C_addrss, I2C_rx_data, 2, 100);
			  I2C_temp = (I2C_rx_data[0]<<8) + I2C_rx_data[1];
			  temp = (float)I2C_temp * 0.0078125;
		  }

		  CDC_Transmit_FS((uint8_t*)"Next measurement in: ", 21);
		  HAL_Delay(10);
		  uint8_t buf[10];
		  uint8_t len_print_buf = float_to_ASCII((float)cntr,buf);
		  CDC_Transmit_FS(buf, len_print_buf);
		  HAL_Delay(10);
		  CDC_Transmit_FS((uint8_t*)" seconds.\n", 10);
		  HAL_Delay(10);
		  CDC_Transmit_FS((uint8_t*)"Press enter to change data.\n", 28);
		  HAL_Delay(10);
		  CDC_Transmit_FS((uint8_t*)"\n", 1);
		  HAL_Delay(10);

		  if(USB_buffer[0] == 13){
			  // second to next measurement
			  CDC_Transmit_FS((uint8_t*)"Fill in seconds for next measurement or press enter to keep old value.\n", 71);
			  HAL_Delay(100);
			  USB_buffer[0] = 82;
			  // change data cntr
			  float val = USB_data(set_cntr);
			  set_cntr = (uint32_t)val;
			  cntr = set_cntr;
			  CDC_Transmit_FS((uint8_t*)"\n", 1);
			  HAL_Delay(100);

			  // change data SWV
			  CDC_Transmit_FS((uint8_t*)"Fill in SWV parameters (see PalmSens.nl) or press enter to keep old values:\n", 76);
			  HAL_Delay(100);
			  CDC_Transmit_FS((uint8_t*)"Equilibration time: ", 20);
			  HAL_Delay(100);
			  swv1.t_equilibration = USB_data(swv1.t_equilibration);
			  CDC_Transmit_FS((uint8_t*)"Amplitude: ", 11);
			  HAL_Delay(100);
			  swv1.Amplitude = USB_data(swv1.Amplitude);
			  CDC_Transmit_FS((uint8_t*)"Frequency: ", 11);
			  HAL_Delay(100);
			  swv1.Frequency = USB_data(swv1.Frequency);
			  CDC_Transmit_FS((uint8_t*)"Begin potential: ", 17);
			  HAL_Delay(100);
			  swv1.E_begin = USB_data(swv1.E_begin);
			  CDC_Transmit_FS((uint8_t*)"End potential: ", 15);
			  HAL_Delay(100);
			  swv1.E_end = USB_data(swv1.E_end);
			  CDC_Transmit_FS((uint8_t*)"Step: ", 6);
			  HAL_Delay(100);
			  swv1.E_step = USB_data(swv1.E_step);
			  CDC_Transmit_FS((uint8_t*)"\n", 1);
			  HAL_Delay(100);

			  // use measurement or update voltammograms?
			  CDC_Transmit_FS((uint8_t*)"Perform voltammogram? Press: yes (y) or no (n).\n\n", 49);
			  HAL_Delay(100);
			  while(USB_buffer[0] == 82);
			  if(USB_buffer[0] == 121){
				  use_measurement = 1;
			  }
			  else{
				  memset(USB_buffer,'0',3000);
				  USB_buffer[0] = 82;
				  CDC_Transmit_FS((uint8_t*)"Update voltammogram? Press: yes (y) or no (n).\n\n", 48);
				  HAL_Delay(100);
				  while(USB_buffer[0] == 82);
				  if(USB_buffer[0] == 121){\
					  // for U and I
					  //USB_get_voltammogram();
					  //USB_get_voltammogram();
				  }
				  memset(USB_buffer,'0',3000);
				  USB_buffer[0] = 82;
				  use_measurement = 0;
			  }

			  // run algorithms
			  CDC_Transmit_FS((uint8_t*)"Run algorithms? Press yes (y) or press no (n).\n\n", 48);
			  HAL_Delay(100);
			  while(USB_buffer[0] == 82);
			  if(USB_buffer[0] == 121){
				  run_algorithms = 1;
			  }
			  else{
				  run_algorithms = 0;
			  }
			  memset(USB_buffer,'0',3000);
			  USB_buffer[0] = 82;
		  }

		if(cntr == 0){
			HAL_GPIO_TogglePin(GPIOA, LED_Pin);
			CDC_Transmit_FS((uint8_t*)"START MEASUREMENT!\n\n", 20);
			HAL_Delay(10);
			if(use_measurement == 1){
				//execute_SWV(swv1);
			}
			if(run_algorithms == 1){
				struct voltammogram nv1 = v1;
				struct voltammogram *pv1 = &nv1;
				baseline_correction(pv1, 1000);
				window(pv1,0.4,1.0);
				get_peak(pv1);
				struct voltammogram gaus = gaussian_fit(*pv1);
				struct voltammogram secondPeak = subGaus(gaus, *pv1);
				secondPeak.length = v1.length;
				struct voltammogram *psp = &secondPeak;
				get_peak(psp);

				float IMTX = 0.0;
				float UMTX = 0.0;
				float LDd = 12.595243113981994*(pv1->peakI - 0.131641016666667) + -88.217138912960830*(pv1->peakU - 0.737234700000000);
				float LDr = 12.595243113981994*(psp->peakI - 0.131641016666667) + -88.217138912960830*(psp->peakI - 0.737234700000000);
				if((LDd < 0) && (LDr > 0)){
				  IMTX = pv1->peakI;
				  UMTX = pv1->peakU;
				}
				else{
				  IMTX = psp->peakI;
				  UMTX = psp->peakI;
				}

				float meanI = IMTX*99.0550;
				float pH_coef_slope = -2.4245*log(meanI)-43.0140;
				float pH_coef_inter = 2.3404*log(meanI)+39.4826;
				float pH_est = pH_coef_slope*UMTX + pH_coef_inter;
				if (pH_est > 8){
				  pH_est = 8;
				}
				else if(pH_est < 2){
				  pH_est = 2;
				}
				pH_est = round(pH_est);

				float fingerPrint[8] = {86.9785924968791, 93.1288806791545, 82.9734509350177, 89.2576238928360, 106.456856768742, 114.085161308293, 120.504521546912};
				float con = fingerPrint[(uint8_t)pH_est - 2]*IMTX;

				// print
				uint8_t buf[10];
				uint8_t len_buf = float_to_ASCII(con, buf);
				CDC_Transmit_FS(buf, len_buf);
				HAL_Delay(10);
				CDC_Transmit_FS((uint8_t*)" uM\n\n", 5);
				HAL_Delay(1000);
			}
			// reset counter
			cntr = set_cntr;
		}
		cntr--;
	    sec_flag = 0;
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10909CEC;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 8000-1;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 10000-1;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */
  HAL_TIM_Base_Start_IT(&htim7);
  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CH_ADC_Pin|CS_DAC_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, PDEN_Pin|MUX_SEL1_Pin|RSTSEL_Pin|LED_Pin
                          |EN_4_2VDC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CH_SEL_GPIO_Port, CH_SEL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MUX_SEL2_Pin|EN_REF_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CH_ADC_Pin PDEN_Pin CS_DAC_Pin MUX_SEL1_Pin
                           RSTSEL_Pin LED_Pin EN_4_2VDC_Pin */
  GPIO_InitStruct.Pin = CH_ADC_Pin|PDEN_Pin|CS_DAC_Pin|MUX_SEL1_Pin
                          |RSTSEL_Pin|LED_Pin|EN_4_2VDC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : CH_SEL_Pin MUX_SEL2_Pin EN_REF_Pin */
  GPIO_InitStruct.Pin = CH_SEL_Pin|MUX_SEL2_Pin|EN_REF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef * hspi){
	if(hspi == &hspi1){
		SPI_tx_flag = 1;
	}
}

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim){
	if(htim == &htim7){
		sec_flag = 1;
	}
}

float USB_data(float num){
	float val = num;

	while(USB_buffer[0] == 82);
	if(USB_buffer[0] == 13){
	  uint8_t buf[10];
	  uint8_t len_buf = float_to_ASCII(num, buf);
	  CDC_Transmit_FS(buf, len_buf);
	  memset(USB_buffer,'0',3000);
	  USB_buffer[0] = 82;
	  HAL_Delay(10);
	}
	else{
	  val = USB_get_num();
	  uint8_t buf[10];
	  uint8_t len_buf = float_to_ASCII(val, buf);
	  CDC_Transmit_FS(buf, len_buf);
	  HAL_Delay(10);
	}
	CDC_Transmit_FS((uint8_t*)"\n", 1);
	HAL_Delay(10);

	return val;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
