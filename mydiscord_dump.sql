--
-- PostgreSQL database dump
--

-- Dumped from database version 17.4
-- Dumped by pg_dump version 17.4

-- Started on 2025-05-02 13:40:12

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 223 (class 1259 OID 16586)
-- Name: channel_memberships; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.channel_memberships (
    user_id integer NOT NULL,
    channel_id integer NOT NULL,
    role character varying(20) DEFAULT 'member'::character varying
);


ALTER TABLE public.channel_memberships OWNER TO postgres;

--
-- TOC entry 220 (class 1259 OID 16542)
-- Name: channels; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.channels (
    id integer NOT NULL,
    name character varying(100) NOT NULL,
    is_private boolean DEFAULT false,
    members integer[],
    owner_id integer,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP
);


ALTER TABLE public.channels OWNER TO postgres;

--
-- TOC entry 219 (class 1259 OID 16541)
-- Name: channels_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.channels_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.channels_id_seq OWNER TO postgres;

--
-- TOC entry 4894 (class 0 OID 0)
-- Dependencies: 219
-- Name: channels_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.channels_id_seq OWNED BY public.channels.id;


--
-- TOC entry 222 (class 1259 OID 16560)
-- Name: messages; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.messages (
    id integer NOT NULL,
    user_id integer,
    channel_id integer,
    content text,
    is_thread boolean DEFAULT false,
    parent_message_id integer,
    emoji_reactions jsonb,
    encrypted boolean DEFAULT false,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP
);


ALTER TABLE public.messages OWNER TO postgres;

--
-- TOC entry 221 (class 1259 OID 16559)
-- Name: messages_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.messages_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.messages_id_seq OWNER TO postgres;

--
-- TOC entry 4895 (class 0 OID 0)
-- Dependencies: 221
-- Name: messages_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.messages_id_seq OWNED BY public.messages.id;


--
-- TOC entry 218 (class 1259 OID 16529)
-- Name: users; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.users (
    id integer NOT NULL,
    first_name character varying(50),
    last_name character varying(50),
    email character varying(100) NOT NULL,
    password_hash text NOT NULL,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP,
    question_1 text,
    question_2 text,
    salt character varying(64)
);


ALTER TABLE public.users OWNER TO postgres;

--
-- TOC entry 217 (class 1259 OID 16528)
-- Name: users_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.users_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.users_id_seq OWNER TO postgres;

--
-- TOC entry 4896 (class 0 OID 0)
-- Dependencies: 217
-- Name: users_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.users_id_seq OWNED BY public.users.id;


--
-- TOC entry 4711 (class 2604 OID 16545)
-- Name: channels id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channels ALTER COLUMN id SET DEFAULT nextval('public.channels_id_seq'::regclass);


--
-- TOC entry 4714 (class 2604 OID 16563)
-- Name: messages id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.messages ALTER COLUMN id SET DEFAULT nextval('public.messages_id_seq'::regclass);


--
-- TOC entry 4709 (class 2604 OID 16532)
-- Name: users id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users ALTER COLUMN id SET DEFAULT nextval('public.users_id_seq'::regclass);


--
-- TOC entry 4888 (class 0 OID 16586)
-- Dependencies: 223
-- Data for Name: channel_memberships; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.channel_memberships (user_id, channel_id, role) FROM stdin;
1	1	admin
2	1	member
3	1	member
1	2	member
2	2	admin
4	2	moderator
3	3	admin
1	3	member
5	3	member
2	4	admin
3	4	member
1	5	admin
2	5	member
3	5	member
4	5	member
4	6	admin
5	6	member
5	7	admin
1	8	admin
5	8	member
\.


--
-- TOC entry 4885 (class 0 OID 16542)
-- Dependencies: 220
-- Data for Name: channels; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.channels (id, name, is_private, members, owner_id, created_at) FROM stdin;
1	General	f	{1,2,3}	1	2025-05-02 13:04:09.854425
2	Privé	t	{2,4}	2	2025-05-02 13:04:09.854425
3	Développement	f	{1,3,5}	3	2025-05-02 13:04:09.854425
4	Design	f	{2,3}	2	2025-05-02 13:04:09.854425
5	Jeux	f	{1,2,3,4}	1	2025-05-02 13:04:09.854425
6	Musique	f	{4,5}	4	2025-05-02 13:04:09.854425
7	Films	t	{2,5}	5	2025-05-02 13:04:09.854425
8	Cuisine	f	{1,5}	1	2025-05-02 13:04:09.854425
9	Voyage	t	{3,4}	3	2025-05-02 13:04:09.854425
10	Sport	f	{2,3,5}	2	2025-05-02 13:04:09.854425
\.


--
-- TOC entry 4887 (class 0 OID 16560)
-- Dependencies: 222
-- Data for Name: messages; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.messages (id, user_id, channel_id, content, is_thread, parent_message_id, emoji_reactions, encrypted, created_at) FROM stdin;
1	1	1	#.&&%%&%((2,,"&	f	\N	{"😊": [1]}	t	2025-05-02 13:17:01.833348
2	2	1	,@$&'%,*#*# )$+	f	\N	{"🔥": [2]}	t	2025-05-02 13:17:01.833348
3	3	1	#%($+#$%/'%	f	\N	{"👍": [3]}	t	2025-05-02 13:17:01.833348
17	1	1	2.(&"*&$%&*	t	1	{"😂": [1]}	t	2025-05-02 13:18:11.185054
18	2	1	&$,-"*&$)+	t	2	{"😅": [2]}	t	2025-05-02 13:18:11.185054
19	3	1	&.&$+%(#	f	\N	{"🤔": [3]}	t	2025-05-02 13:18:11.185054
20	1	1	,&%/#$(%	f	\N	{"👀": [1, 2]}	t	2025-05-02 13:18:11.185054
21	2	1	%&%&"#)*,#*	t	3	{"😎": [2]}	t	2025-05-02 13:18:11.185054
22	3	1	" *'($)&*%	t	3	{"😡": [3]}	t	2025-05-02 13:18:11.185054
23	1	1	1#*&%,"+#	f	\N	{"🙏": [1]}	t	2025-05-02 13:18:11.185054
\.


--
-- TOC entry 4883 (class 0 OID 16529)
-- Dependencies: 218
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.users (id, first_name, last_name, email, password_hash, created_at, question_1, question_2, salt) FROM stdin;
1	Alice	Johnson	alice.johnson@example.com	f9d0c6a69cb9ebdc4c8d39b36b03b9b159f5089ecff7b827618907945458cc56	2025-04-18 06:29:19.836302	Shrek	Balut	6a1f8c6d13b88d0ea9c5aafdbccfa340
2	Elti	Smith	elti.smith@example.com	7f4c1d7b0f5b9b091d2b5c9ea67fc38f3b3b87b4d9efad69b90b50f3ad4f4d22	2025-04-18 06:29:19.836302	SpongeBob	Durian	1a48b9bb4f927da10576b71fcb7d9eab
3	Chris	Brown	chris.brown@example.com	5f4b635f2e5b1e5e31cf2a90cd39452c8e2f30ff5904d019ff7b12378639f2f6'	2025-04-18 06:29:19.836302	Bugs	Haggis	34bc70969fc04b13b19dfc10409c0da9
4	Diana	Miller	diana.miller@example.com	dd8b5401cb0803de2a1cc54fcbb59272e9b85a6bc348e9a4cd80ec9642e86b76	2025-04-18 06:29:19.836302	Goofy	Escargot	2d7fe356226fdba76fdb61b76b8eae2a
5	Fiona	Davis	fiona.davis@example.com	7f51e7bdb0fbbaf23f64f2b8b0214ec59ed39f426be57ff71ad556fb015b4652	2025-04-18 08:01:36.625345	Jerry	Tripe	fd836dc46296372d0e1b6db8b0d75085
6	George	Evans	george.evans@example.com	4b75d81ac1fc3a4d7c2d26a3e209438c1a080ccd55c9de67e2f6ff705202dcfa	2025-04-18 08:01:36.625345	Naruto	grenouille	ce1bfae5e4260f615e20a9b6c32c6b33
7	Leila	Wilson	leila.wilson@example.com	6fe027bcb4069287368e18a1412b4e215c8b4505378df9a7f8e00a96de1fe8ad	2025-04-18 08:01:36.625345	Simba	Natto	4a8935b79c209ae474e09a850f9d8317
8	Vanessa	Taylor	vanessa.taylor@example.com	32e5d0bdbf7f2b72e0a815e53f1a1b88feaa740eae5d88a29cfed73252c2fbe3	2025-04-18 08:01:36.625345	Pikachu	Tofu	ad1cc5406f4b9e397f76ff24b4d22cde
9	Julia	Moore	julia.moore@example.com	2d13e9f09a826c7be78c10e67d7acb77e07392e98a6a623cf05a4c20a825f931	2025-04-18 08:01:36.625345	Tom	Insects	d417b315228ca80b88b274f68e59e825
10	Yuliia	Sherstiuk	yuliia.sherstiuk@laplateforme.io	16b4f47d2cf97856b3774d9e9d64e44cc413b0dbd0ec7a035a3748e508d6f1ed	2025-04-25 15:23:13.431333	Balto	Escargot	e9e6b5987d36bfb6d68d1d079db1a34b
11	eltigani	Abdallah	eltigani.abdallah@laplateforme.io	98c674ba12f4e9c740ba946a8ef6b8e3493a3b43c7e1f498589539f5387e8e11	2025-04-28 09:47:04.86208	mama bear	milkshake mangue	fa99e6fe99183b2225b1b94969307272
12	christine	ka	christine.chemali@laplateforme.io	b16b9d51d92d0f6cb5f2fbbbeb051f24c520cb7dbd215d50a2e7d2ec929cb86d	2025-04-28 12:56:53.134554	Fiona	Durian	6092f14b909d2a086d615d22c88a8ac1
\.


--
-- TOC entry 4897 (class 0 OID 0)
-- Dependencies: 219
-- Name: channels_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.channels_id_seq', 13, true);


--
-- TOC entry 4898 (class 0 OID 0)
-- Dependencies: 221
-- Name: messages_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.messages_id_seq', 23, true);


--
-- TOC entry 4899 (class 0 OID 0)
-- Dependencies: 217
-- Name: users_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.users_id_seq', 13, true);


--
-- TOC entry 4730 (class 2606 OID 16591)
-- Name: channel_memberships channel_memberships_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channel_memberships
    ADD CONSTRAINT channel_memberships_pkey PRIMARY KEY (user_id, channel_id);


--
-- TOC entry 4724 (class 2606 OID 16553)
-- Name: channels channels_name_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channels
    ADD CONSTRAINT channels_name_key UNIQUE (name);


--
-- TOC entry 4726 (class 2606 OID 16551)
-- Name: channels channels_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channels
    ADD CONSTRAINT channels_pkey PRIMARY KEY (id);


--
-- TOC entry 4728 (class 2606 OID 16570)
-- Name: messages messages_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.messages
    ADD CONSTRAINT messages_pkey PRIMARY KEY (id);


--
-- TOC entry 4720 (class 2606 OID 16540)
-- Name: users users_email_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_email_key UNIQUE (email);


--
-- TOC entry 4722 (class 2606 OID 16538)
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);


--
-- TOC entry 4735 (class 2606 OID 16597)
-- Name: channel_memberships channel_memberships_channel_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channel_memberships
    ADD CONSTRAINT channel_memberships_channel_id_fkey FOREIGN KEY (channel_id) REFERENCES public.channels(id) ON DELETE CASCADE;


--
-- TOC entry 4736 (class 2606 OID 16592)
-- Name: channel_memberships channel_memberships_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channel_memberships
    ADD CONSTRAINT channel_memberships_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id) ON DELETE CASCADE;


--
-- TOC entry 4731 (class 2606 OID 16554)
-- Name: channels channels_owner_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channels
    ADD CONSTRAINT channels_owner_id_fkey FOREIGN KEY (owner_id) REFERENCES public.users(id) ON DELETE SET NULL;


--
-- TOC entry 4732 (class 2606 OID 16576)
-- Name: messages messages_channel_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.messages
    ADD CONSTRAINT messages_channel_id_fkey FOREIGN KEY (channel_id) REFERENCES public.channels(id) ON DELETE CASCADE;


--
-- TOC entry 4733 (class 2606 OID 16581)
-- Name: messages messages_parent_message_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.messages
    ADD CONSTRAINT messages_parent_message_id_fkey FOREIGN KEY (parent_message_id) REFERENCES public.messages(id) ON DELETE CASCADE;


--
-- TOC entry 4734 (class 2606 OID 16571)
-- Name: messages messages_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.messages
    ADD CONSTRAINT messages_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id) ON DELETE SET NULL;


-- Completed on 2025-05-02 13:40:12

--
-- PostgreSQL database dump complete
--

