class vetor_3d {
	public:
	float coord[3];

	vetor_3d(float v_x, float v_y, float v_z);

	void invert_direction();

	void get_unitary_vector();

	float scalar_prod(vetor_3d vetor_2);

	void reset_coord(float x, float y, float z);

	vetor_3d vector_sum(vetor_3d vetor_2, vetor_3d result);

	void log_coords();

	void transf_coord_from_spher_to_cart(float r, float theta_rad, float phi_rad);
};

int NDA_calculation(int month_day, int month);

void log_entrada(int NDA, float latitude, float local_time);

void log_angulos(float * sin_Alt_sin_Azim_Array );

void log_sun_position(vetor_3d s);

vetor_3d get_normal_vector(vetor_3d sun_pos, vetor_3d helios_pos, vetor_3d focus_pos, vetor_3d result);

vetor_3d get_unitary_vector(vetor_3d v, vetor_3d result);

float rad_to_deg(float rad);

float deg_to_rad(float deg);

float ang_hor_rad(float hora_local);

float decl_calculation(int NDA);

float sin_Alt_calculation(int NDA, float lat, float local_time);

float sin_Azim_calculation(int NDA, float lat, float local_time);

vetor_3d sun_pos_in_cartesian_coord(float sin_Alt, float sin_Azim, vetor_3d result);

//calcula a constante solar corrigida devido à variação na distância Terra-Sol ~ (d/D)^2
float J_elliptic_correction(int NDA);

//distância de atmosfera cortada pelo raio de luz em termos do ângulo zenital
float atm_cross_distance(float zenital_angle);

float refl_power_from_scalar_product(vetor_3d n, vetor_3d s, float J_bare);

//retorna o fator de correção devido à excentricidade da órbita da Terra ~  (d/D)^2
float elliptic_correction_factor(int NDA);

vetor_3d get_sun_position(float NDA, float lat, float hora_local, vetor_3d result);

float one_mirror_power(vetor_3d s, vetor_3d R, int NDA);

//retorna true se o heliostato estiver na sombra da torre
bool tower_shadow_cil_aprox(float tower_radius, float tower_height, vetor_3d helios_pos, vetor_3d sun);
